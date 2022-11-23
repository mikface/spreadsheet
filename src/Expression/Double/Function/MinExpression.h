//
// Created by mikoun on 15.06.21.
//

#ifndef SPREADSHEET_MINEXPRESSION_H
#define SPREADSHEET_MINEXPRESSION_H


#include "../FunctionExpression.h"

class MinExpression : public FunctionExpression {
public:
    /**
     * Initializes min function expression with two arguments (numbers/references)
     * @param innerExpr
     * @param secondInnerExpr
     */
    MinExpression(const std::shared_ptr<DoubleExpression> &innerExpr,
                  std::shared_ptr<DoubleExpression> secondInnerExpr);

    /**
     * @inherit
     */
    double getValue() const override;

private:
    /**
     * Second argument
     */
    std::shared_ptr<DoubleExpression> secondExpr;
};


#endif //SPREADSHEET_MINEXPRESSION_H
