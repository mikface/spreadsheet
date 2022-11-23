//
// Created by mikoun on 26.03.21.
//

#include "NumberCell.h"

NumberCell::NumberCell(const std::string& content, double doubleContent): Cell(content), doubleContent(doubleContent) {
}

double NumberCell::doubleValue() const {
    return doubleContent;
}
