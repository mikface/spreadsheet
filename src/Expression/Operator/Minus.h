//
// Created by mikoun on 13.06.21.
//

#ifndef SPREADSHEET_MINUS_H
#define SPREADSHEET_MINUS_H


#include "../OperatorExpression.h"

class Minus : public OperatorExpression{
public:
    /** Initializes binary Minus operator, sets operator priority */
    Minus();

    /** Evaluates expression (NumberA - NumberB) */
    double evaluate(double leftOperand, double rightOperand) override;

};


#endif //SPREADSHEET_MINUS_H
