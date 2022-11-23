//
// Created by mikoun on 13.06.21.
//

#ifndef SPREADSHEET_DIVIDE_H
#define SPREADSHEET_DIVIDE_H


#include "../OperatorExpression.h"

class Divide : public OperatorExpression{
public:
    /** Initializes binary Divide operator, sets operator priority */
    Divide();

    /** Evaluates expression (NumberA/NumberB) */
    double evaluate(double leftOperand, double rightOperand) override;
};


#endif //SPREADSHEET_DIVIDE_H
