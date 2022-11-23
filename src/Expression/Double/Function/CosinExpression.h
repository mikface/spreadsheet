//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_COSINEXPRESSION_H
#define SPREADSHEET_COSINEXPRESSION_H

#include <cmath>
#include "../FunctionExpression.h"

class CosinExpression : public FunctionExpression {
public:
    /**
     * Initializes cosin function expression with one argument (number/reference)
     * @param innerExpr
     */
    explicit CosinExpression(const std::shared_ptr<DoubleExpression> &innerExpr);

    /**
     * @inherit
     */
    double getValue() const override;
};


#endif //SPREADSHEET_COSINEXPRESSION_H
