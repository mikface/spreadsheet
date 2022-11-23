//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_NUMBEREXPRESSION_H
#define SPREADSHEET_NUMBEREXPRESSION_H


#include "../DoubleExpression.h"

class NumberExpression : public DoubleExpression {
public:
    /**
     * Initializes direct operand (number) expression
     * @param value
     */
    explicit NumberExpression(double value);

    /**
     * @inherit
     */
    double getValue() const override;

private:
    /**
     * Direct operand
     */
    double value;
};


#endif //SPREADSHEET_NUMBEREXPRESSION_H
