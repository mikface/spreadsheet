//
// Created by mikoun on 13.06.21.
//

#ifndef SPREADSHEET_TIMES_H
#define SPREADSHEET_TIMES_H


#include "../OperatorExpression.h"

class Times : public OperatorExpression{
public:
    /** Initializes binary Times operator, sets operator priority */
    Times();

    /** Evaluates expression (NumberA * NumberB) */
    double evaluate(double leftOperand, double rightOperand) override;
};


#endif //SPREADSHEET_TIMES_H
