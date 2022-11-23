//
// Created by mikoun on 31.05.21.
//

#include "CosinExpression.h"

CosinExpression::CosinExpression(const std::shared_ptr<DoubleExpression> &innerExpr): FunctionExpression(innerExpr) {

}

double CosinExpression::getValue() const {
    return cos(innerExpression->getValue());
}
