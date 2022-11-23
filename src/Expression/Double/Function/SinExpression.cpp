//
// Created by mikoun on 31.05.21.
//

#include "SinExpression.h"

SinExpression::SinExpression(const std::shared_ptr<DoubleExpression> &innerExpr): FunctionExpression(innerExpr) {
}

double SinExpression::getValue() const {
    return sin(innerExpression->getValue());
}
