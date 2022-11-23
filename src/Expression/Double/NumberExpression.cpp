//
// Created by mikoun on 31.05.21.
//

#include "NumberExpression.h"

double NumberExpression::getValue() const {
    return value;
}

NumberExpression::NumberExpression(double value) : value(value) {

}
