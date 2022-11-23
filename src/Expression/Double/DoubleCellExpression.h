//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_DOUBLECELLEXPRESSION_H
#define SPREADSHEET_DOUBLECELLEXPRESSION_H


#include <memory>
#include "../DoubleExpression.h"
#include "../../Cell/NumberCell.h"
#include "../../Core/Spreadsheet.h"

class DoubleCellExpression : public DoubleExpression{
public:
    /**
     * Initializes expression with reference to other NumberCell
     */
    explicit DoubleCellExpression(std::shared_ptr<NumberCell>);

    /**
     * @inherit
     */
    double getValue() const override;
private:
    /**
     * Number cell reference
     */
    std::shared_ptr<NumberCell> cell;
};


#endif //SPREADSHEET_DOUBLECELLEXPRESSION_H
