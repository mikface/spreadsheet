//
// Created by mikoun on 13.06.21.
//

#include "Divide.h"

Divide::Divide() : OperatorExpression(TIMES_DIVIDE_PRIORITY) {

}

double Divide::evaluate(double leftOperand, double rightOperand) {

    return rightOperand == 0 ? 0 : (leftOperand / rightOperand);
}
