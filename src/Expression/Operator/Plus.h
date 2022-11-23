//
// Created by mikoun on 13.06.21.
//

#ifndef SPREADSHEET_PLUS_H
#define SPREADSHEET_PLUS_H


#include "../OperatorExpression.h"

class Plus : public OperatorExpression{
public:
    /** Initializes binary Plus operator, sets operator priority */
    Plus();

    /** Evaluates expression (NumberA + NumberB) */
    double evaluate(double leftOperand, double rightOperand) override;
};


#endif //SPREADSHEET_PLUS_H
