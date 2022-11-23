//
// Created by mikoun on 13.06.21.
//

#ifndef SPREADSHEET_OPERATOREXPRESSION_H
#define SPREADSHEET_OPERATOREXPRESSION_H
#define PLUS_MINUS_PRIORITY 0
#define TIMES_DIVIDE_PRIORITY 1

#include "Expression.h"

class OperatorExpression : public Expression {
public:
    /**
     * Initializes operator expression
     * @param priority
     */
    explicit OperatorExpression(int priority);

    /**
     * Needed for polymorphism
     */
    virtual ~OperatorExpression() = default;

    /**
     * Returns priority of operator (higher number, higher the priority)
     * @return
     */
    virtual int getPriority();

    /**
     * Pure virtual method for evaluating operator expressions
     * @param leftOperand
     * @param rightOperand
     * @return
     */
    virtual double evaluate(double leftOperand, double rightOperand) = 0;

protected:
    /**
     * Operator priority
     */
    int priority;
};


#endif //SPREADSHEET_OPERATOREXPRESSION_H
