//
// Created by mikoun on 31.05.21.
//

#include "DoubleCellExpression.h"

DoubleCellExpression::DoubleCellExpression(std::shared_ptr<NumberCell> cell) : cell(std::move(cell)) {

}

double DoubleCellExpression::getValue() const {
    return cell->doubleValue();
}
