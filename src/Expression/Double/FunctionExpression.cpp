//
// Created by mikoun on 01.06.21.
//

#include "FunctionExpression.h"

FunctionExpression::FunctionExpression(std::shared_ptr<DoubleExpression> innerExpr):innerExpression(std::move(innerExpr)) {
}
