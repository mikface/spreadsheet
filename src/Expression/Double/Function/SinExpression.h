//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_SINEXPRESSION_H
#define SPREADSHEET_SINEXPRESSION_H

#include <cmath>
#include "../FunctionExpression.h"

class SinExpression : public FunctionExpression{
public:
    /**
     * Initializes cosin function expression with one argument (number/reference)
     * @param innerExpr
     */
    explicit SinExpression(const std::shared_ptr<DoubleExpression>& innerExpr);

    /**
     * @inherit
     */
    double getValue() const override;
};


#endif //SPREADSHEET_SINEXPRESSION_H
