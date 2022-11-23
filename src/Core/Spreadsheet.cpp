//
// Created by mikoun on 26.03.21.
//

#include "Spreadsheet.h"

void Spreadsheet::saveCellContent(const Cell::Coord &coordinates, const std::string &content) {
    auto address = Cell::coordToAddress(coordinates);
    saveCellContentByAddress(address, content);
}

std::string Spreadsheet::getCellContent(const Cell::Coord &coordinates) const {
    auto it = cells.find(Cell::coordToAddress(coordinates));
    if (it == cells.end()) {
        return "";
    }

    return it->second->value();
}

std::string Spreadsheet::getCellDisplayContent(const Cell::Coord &coordinates) const {
    auto it = cells.find(Cell::coordToAddress(coordinates));
    if (it == cells.end()) {
        return "";
    }

    return it->second->displayValue();
}

std::shared_ptr<Cell> Spreadsheet::getCellByAddress(const std::string &address) const {
    auto it = cells.find(address);

    return it == cells.end() ? nullptr : it->second;
}


std::shared_ptr<FunctionCell>
Spreadsheet::parseFunctionCellContent(const std::string &content, const std::string &newCellAddress) {
    /** stack for shunting yard */
    std::stack<std::shared_ptr<OperatorExpression>> operatorExpressionStack;
    std::stack<int> parenthesisStack;
    int operatorsBetweenParenthesis;
    /** tokenize expression */
    std::istringstream ss(content.substr(1));
    std::string token;
    std::shared_ptr<OperatorExpression> newOperator;
    std::shared_ptr<Expression> expressionPtr;
    auto returnCell = std::make_shared<FunctionCell>(content);
    int state = EXPECTING_EXPRESSION;

    /** parse token by token */
    while (ss >> token) {
        switch (state) {
            case EXPECTING_EXPRESSION:
                if (token == "(") {
                    parenthesisStack.push(0);
                    break;
                } else {
                    expressionPtr = parseExpression(token, newCellAddress);
                    if (expressionPtr != nullptr) {
                        returnCell->addExpression(expressionPtr);
                        state = EXPECTING_OPERATOR;
                        break;
                    }
                }

                /** NO EXPRESSION MATCH => ERROR */
                throw std::invalid_argument("Unknown expression");
            case EXPECTING_OPERATOR:
                if (token == ")") {
                    operatorsBetweenParenthesis = parenthesisStack.top();
                    parenthesisStack.pop();
                    while (operatorsBetweenParenthesis-- > 0) {
                        returnCell->addExpression(operatorExpressionStack.top());
                        operatorExpressionStack.pop();
                    }
                } else {
                    newOperator = parseOperator(token);

                    if (newOperator == nullptr) {
                        throw std::invalid_argument("Unknown operator");
                    }

                    /** precedence */
                    while (!operatorExpressionStack.empty() &&
                           newOperator->getPriority() < operatorExpressionStack.top()->getPriority()) {
                        if (!parenthesisStack.empty() && parenthesisStack.top() <= 0) {
                            break;
                        }
                        returnCell->addExpression(operatorExpressionStack.top());
                        operatorExpressionStack.pop();
                        if (!parenthesisStack.empty()) {
                            operatorsBetweenParenthesis = parenthesisStack.top();
                            operatorsBetweenParenthesis--;
                            parenthesisStack.pop();
                            parenthesisStack.push(operatorsBetweenParenthesis);
                        }
                    }
                    if (!parenthesisStack.empty()) {
                        operatorsBetweenParenthesis = parenthesisStack.top();
                        operatorsBetweenParenthesis++;
                        parenthesisStack.pop();
                        parenthesisStack.push(operatorsBetweenParenthesis);
                    }
                    operatorExpressionStack.push(newOperator);

                    state = EXPECTING_EXPRESSION;
                    break;
                }
        }
    }

    /** last token is operator - error */
    if (state == EXPECTING_EXPRESSION) {
        throw std::invalid_argument("Invalid expression");
    }

    if (!parenthesisStack.empty()) {
        throw std::invalid_argument("Parenthesis don't match");
    }

    /** cycle detection */
    if (graph->hasCycle()) {
        throw std::logic_error("Cycle detected");
    }

    /** valid expression, empty stack */
    while (!operatorExpressionStack.empty()) {
        returnCell->addExpression(operatorExpressionStack.top());
        operatorExpressionStack.pop();
    }

    return returnCell;
}

std::shared_ptr<Cell>
Spreadsheet::createCellFromContent(const std::string &content, const std::string &newCellAddress) {

    std::shared_ptr<Cell> newCell;

    /** FUNCTION CELL */
    if (content.at(0) == '=') {
        try {
            newCell = parseFunctionCellContent(content, newCellAddress);
        } catch (std::invalid_argument &ex) {
            newCell = std::make_shared<StringCell>("Error");
        } catch (std::logic_error &) {
            newCell = std::make_shared<StringCell>("Cycle detected");
        }
        return newCell;
    }

    /** NUMERIC CELL */
    auto numericRegex = std::regex("^-?[0-9][0-9,\\.]*$");
    if (std::regex_match(content, numericRegex)) {
        double doubleContent = std::stod(content);
        newCell = std::make_shared<NumberCell>(content, doubleContent);
        return newCell;
    }

    /** STRING CELL */
    newCell = std::make_shared<StringCell>(content);


    return newCell;
}

void Spreadsheet::saveCellContentByAddress(const std::string &address, const std::string &content) {
    auto it = cells.find(address);

    /** NEW CELL */
    if (it == cells.end()) {
        if (content.empty()) {
            return;
        }
        it = cells.emplace(address, createCellFromContent(content, address)).first;
        it->second->setAddress(address);
    } else {
        /** erase old content */
        cells.erase(address);
        graph->eraseCellDependencies(address);
        if (!content.empty()) {
            /** different content, new cell created */
            it = cells.insert(
                    std::map<std::string, std::shared_ptr<Cell>>::value_type(
                            address,
                            createCellFromContent(content, address)
                    )
            ).first;
            it->second->setAddress(address);
        }
    }

    /** connected cells refresh */
    for (const auto &i:graph->dependOnMeCells(address)) {
        auto dependentCell = getCellByAddress(i);
        saveCellContentByAddress(dependentCell->getAddress(), dependentCell->value());
    }

}

Spreadsheet::Spreadsheet() {
    graph = std::make_unique<Graph>();
}

std::shared_ptr<DoubleExpression>
Spreadsheet::parseExpression(const std::string &token, const std::string &newCellAddress) {
    std::smatch matches;
    std::shared_ptr<DoubleExpression> functionInnerExpression;
    std::shared_ptr<DoubleExpression> functionSecondInnerExpression;

    /** cell reference */
    if (std::regex_match(token, std::regex("^[A-Z](1[0-9]|2[0-5]|[1-9])$"))) {
        auto cell = getCellByAddress(token);
        if (cell == nullptr) {
            throw std::invalid_argument("Cell empty");
        }
        if (auto numberCell = std::dynamic_pointer_cast<NumberCell>(cell)) {
            /** add edge to graph (cycles, refreshing of cells) */
            graph->addEdge(newCellAddress, numberCell->getAddress());
            return std::make_shared<DoubleCellExpression>(numberCell);
        }

        throw std::invalid_argument("String cell can't be used in expressions");
    }

    /** number */
    if (std::regex_match(token, std::regex("^-?[0-9][0-9,\\.]*$"))) {
        return std::make_shared<NumberExpression>(std::stod(token));
    }

    /** FUNCTIONS */
    /** sin */
    if (std::regex_search(token, matches, std::regex("^(sin|SIN)\\((.+)\\)$"))) {
        if (matches.size() == 3) {
            functionInnerExpression = parseExpression(matches[2].str(), newCellAddress);
            if (functionInnerExpression != nullptr) {
                return std::make_shared<SinExpression>(functionInnerExpression);
            }
        }
    }

    /** cosin */
    if (std::regex_search(token, matches, std::regex("^(cos|COS)\\((.+)\\)$"))) {
        if (matches.size() == 3) {
            functionInnerExpression = parseExpression(matches[2].str(), newCellAddress);
            if (functionInnerExpression != nullptr) {
                return std::make_shared<CosinExpression>(functionInnerExpression);
            }
        }
    }

    /** max */
    if (std::regex_search(token, matches, std::regex("^(max|MAX)\\((.+);(.+)\\)$"))) {
        if (matches.size() == 4) {
            functionInnerExpression = parseExpression(matches[2].str(), newCellAddress);
            functionSecondInnerExpression = parseExpression(matches[3].str(), newCellAddress);
            if (functionInnerExpression != nullptr && functionSecondInnerExpression != nullptr) {
                return std::make_shared<MaxExpression>(functionInnerExpression, functionSecondInnerExpression);
            }
        }
    }

    /** min */
    if (std::regex_search(token, matches, std::regex("^(min|MIN)\\((.+);(.+)\\)$"))) {
        if (matches.size() == 4) {
            functionInnerExpression = parseExpression(matches[2].str(), newCellAddress);
            functionSecondInnerExpression = parseExpression(matches[3].str(), newCellAddress);
            if (functionInnerExpression != nullptr && functionSecondInnerExpression != nullptr) {
                return std::make_shared<MinExpression>(functionInnerExpression, functionSecondInnerExpression);
            }
        }
    }

    return nullptr;
}

std::shared_ptr<OperatorExpression> Spreadsheet::parseOperator(const std::string &token) {
    if (token == "+") {
        return std::make_shared<Plus>();
    }
    if (token == "-") {
        return std::make_shared<Minus>();
    }
    if (token == "*") {
        return std::make_shared<Times>();
    }
    if (token == "/") {
        return std::make_shared<Divide>();
    }

    return nullptr;
}

std::map<std::string, std::shared_ptr<Cell>>
Spreadsheet::getAllCells() const {
    return cells;
}

void Spreadsheet::clearSpreadsheet() {
    cells.clear();
    graph->clear();
}




