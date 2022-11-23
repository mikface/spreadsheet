//
// Created by mikoun on 13.06.21.
//

#include "Plus.h"

Plus::Plus() : OperatorExpression(PLUS_MINUS_PRIORITY) {
}

double Plus::evaluate(double leftOperand, double rightOperand) {
    return leftOperand + rightOperand;
}
