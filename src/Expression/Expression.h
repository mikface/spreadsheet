//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_EXPRESSION_H
#define SPREADSHEET_EXPRESSION_H


class Expression {
public:
    /**
     * Needed for polymorphism, base expression destructor
     */
    virtual ~Expression() = default;
};


#endif //SPREADSHEET_EXPRESSION_H
