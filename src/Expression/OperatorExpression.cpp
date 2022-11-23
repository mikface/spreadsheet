//
// Created by mikoun on 13.06.21.
//

#include "OperatorExpression.h"

OperatorExpression::OperatorExpression(int priority) : priority(priority) {

}

int OperatorExpression::getPriority() {
    return priority;
}
