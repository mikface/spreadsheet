//
// Created by mikoun on 26.03.21.
//

#include <iostream>
#include <utility>
#include "Cell.h"


std::string Cell::coordToAddress(const Cell::Coord &coord) {
    std::string output(1, (char) (coord.fromLeft + 'A'));
    return output.append(std::to_string(coord.fromTop + 1));
}

Cell::Cell(std::string content): content(std::move(content)) {
}

void Cell::setAddress(const std::string& newAddress) {
    address = newAddress;
}

char Cell::colIndexToChar(int column) {
    return (char) (column + 'A');
}

Cell::Coord::Coord() : fromLeft(0), fromTop(0) {
}

Cell::Coord::Coord(int fromLeftVal, int fromTopVal) {
    if (fromLeftVal < 0 || fromTopVal < 0) {
        throw std::invalid_argument("Minus cell coordinates.");
    }
    if (fromLeftVal > MAX_COL || fromTopVal > MAX_ROW) {
        throw std::runtime_error("Trying to initialize a cell out of spreadsheet bounds.");
    }
    fromLeft = fromLeftVal;
    fromTop = fromTopVal;
}

std::string Cell::value() const {
    return content;
}

std::string Cell::displayValue() const {
    return value();
}

std::string Cell::getAddress() const {
    return address;
}
