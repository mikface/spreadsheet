//
// Created by mikoun on 26.03.21.
//

#ifndef SPREADSHEET_STRINGCELL_H
#define SPREADSHEET_STRINGCELL_H


#include "Cell.h"

class StringCell : public Cell {
public:
    /**
     * Initializes string cell with its contents
     * @param content
     */
    explicit StringCell(const std::string& content);
};


#endif //SPREADSHEET_STRINGCELL_H
