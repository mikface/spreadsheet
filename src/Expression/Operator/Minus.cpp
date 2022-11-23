//
// Created by mikoun on 13.06.21.
//

#include "Minus.h"

Minus::Minus() : OperatorExpression(PLUS_MINUS_PRIORITY) {

}

double Minus::evaluate(double leftOperand, double rightOperand) {
    return leftOperand - rightOperand;
}
