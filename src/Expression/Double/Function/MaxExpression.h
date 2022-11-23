//
// Created by mikoun on 15.06.21.
//

#ifndef SPREADSHEET_MAXEXPRESSION_H
#define SPREADSHEET_MAXEXPRESSION_H


#include "../FunctionExpression.h"

class MaxExpression : public FunctionExpression {
public:
    /**
     * Initializes max function expression with two arguments (numbers/references)
     * @param innerExpr
     * @param secondInnerExpr
     */
    MaxExpression(const std::shared_ptr<DoubleExpression> &innerExpr,
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


#endif //SPREADSHEET_MAXEXPRESSION_H
