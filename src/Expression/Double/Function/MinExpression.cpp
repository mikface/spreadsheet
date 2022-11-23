//
// Created by mikoun on 15.06.21.
//

#include "MinExpression.h"


MinExpression::MinExpression(const std::shared_ptr<DoubleExpression> &innerExpr,
                             std::shared_ptr<DoubleExpression> secondInnerExpr):
        FunctionExpression(innerExpr), secondExpr(std::move(secondInnerExpr)) {

}

double MinExpression::getValue() const {
    return innerExpression->getValue() < secondExpr->getValue() ? innerExpression->getValue() : secondExpr->getValue();
}