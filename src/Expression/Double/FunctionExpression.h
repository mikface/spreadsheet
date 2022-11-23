//
// Created by mikoun on 01.06.21.
//

#ifndef SPREADSHEET_FUNCTIONEXPRESSION_H
#define SPREADSHEET_FUNCTIONEXPRESSION_H

#include <memory>
#include "../DoubleExpression.h"

class FunctionExpression : public DoubleExpression{
public:
    /**
     * Base constructor for all Functions, sets first argument
     * @param innerExpr
     */
    explicit FunctionExpression(std::shared_ptr<DoubleExpression> innerExpr);
protected:
    /**
     * First argument
     */
    std::shared_ptr<DoubleExpression> innerExpression;
};


#endif //SPREADSHEET_FUNCTIONEXPRESSION_H
