//
// Created by mikoun on 27.05.21.
//

#include "FunctionCell.h"

FunctionCell::FunctionCell(const std::string &content) : NumberCell(content, 0) {
}

std::string FunctionCell::displayValue() const {
    return std::to_string(doubleValue());
}

double FunctionCell::doubleValue() const {
    std::stack<double> numberStack;
    std::shared_ptr<Expression> currentExpression;
    auto tempQueue = postfixExpression;
    double result, firstOperand, secondOperand;

    while (!tempQueue.empty()) {
        currentExpression = tempQueue.front();
        tempQueue.pop();

        /** operator */
        if (auto *op = dynamic_cast<OperatorExpression *>(currentExpression.get())) {
            secondOperand = numberStack.top();
            numberStack.pop();
            firstOperand = numberStack.top();
            numberStack.pop();
            result = op->evaluate(firstOperand, secondOperand);
        }

        /** number */
        if (auto *number = dynamic_cast<DoubleExpression *>(currentExpression.get())) {
            result = number->getValue();
        }

        numberStack.push(result);
    }

    return numberStack.top();
}

void FunctionCell::addExpression(const std::shared_ptr<Expression>& ptr) {
    postfixExpression.push(ptr);
}
