//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_DOUBLEEXPRESSION_H
#define SPREADSHEET_DOUBLEEXPRESSION_H


#include "Expression.h"

class DoubleExpression : public Expression {
public:
    ~DoubleExpression() = default;

    /**
     * Base virtual method for all double returning expressions (number, references, functions...)
     * @return
     */
    virtual double getValue() const = 0;
};


#endif //SPREADSHEET_DOUBLEEXPRESSION_H
