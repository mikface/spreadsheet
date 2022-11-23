//
// Created by mikoun on 26.03.21.
//

#ifndef SPREADSHEET_NUMBERCELL_H
#define SPREADSHEET_NUMBERCELL_H


#include "Cell.h"

class NumberCell : public Cell {
public:
    /**
     * Initializes number cell (cell holding integer or decimal number)
     * @param content
     * @param doubleContent
     */
    explicit NumberCell(const std::string &content, double doubleContent);

    /**
     * Returns numeric representation of contents
     * @return
     */
    virtual double doubleValue() const;

protected:
    /**
     * Decimal contents of the cell
     */
    double doubleContent;
};


#endif //SPREADSHEET_NUMBERCELL_H
