//
// Created by mikoun on 13.06.21.
//

#include "Times.h"

Times::Times(): OperatorExpression(TIMES_DIVIDE_PRIORITY) {

}

double Times::evaluate(double leftOperand, double rightOperand) {
    return leftOperand * rightOperand;
}
