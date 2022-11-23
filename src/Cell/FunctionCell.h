//
// Created by mikoun on 27.05.21.
//

#ifndef SPREADSHEET_FUNCTIONCELL_H
#define SPREADSHEET_FUNCTIONCELL_H
#define EXPECTING_OPERATOR 0
#define EXPECTING_EXPRESSION 1

#include <regex>
#include <sstream>
#include <iostream>
#include <queue>
#include "Cell.h"
#include "../Expression/Expression.h"
#include "../Expression/OperatorExpression.h"
#include "../Expression/Double/NumberExpression.h"
#include "../Cell/NumberCell.h"

class FunctionCell : public NumberCell {
public:
    /**
     * Constructs function cell, calls base class constructor
     * @param content
     */
    explicit FunctionCell(const std::string &content);

    /**
     * Shows result of the FunctionCell formula for printing in the spreadsheet
     * @return
     */
    std::string displayValue() const override;

    /**
     * Returns decimal number to be used in other formulas or expressions
     * @return
     */
    double doubleValue() const override;

    /**
     * Adds Expression to FunctionCell (operator, number, reference)
     * @param ptr
     */
    void addExpression(const std::shared_ptr<Expression>& ptr);
private:
    /**
     * Postfix representation of formula, ready for calculation by shunting yard
     */
    std::queue<std::shared_ptr<Expression>> postfixExpression;
};


#endif //SPREADSHEET_FUNCTIONCELL_H
