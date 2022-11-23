//
// Created by mikoun on 26.03.21.
//

#ifndef SPREADSHEET_SPREADSHEET_H
#define SPREADSHEET_SPREADSHEET_H

#include <string>
#include <memory>
#include <map>
#include "../Cell/Cell.h"
#include "../Cell/FunctionCell.h"
#include "../Cell/StringCell.h"
#include "../Core/Graph.h"
#include "../Expression/Double/DoubleCellExpression.h"
#include "../Expression/Double/Function/SinExpression.h"
#include "../Expression/Double/Function/CosinExpression.h"
#include "../Expression/Double/Function/MaxExpression.h"
#include "../Expression/Double/Function/MinExpression.h"
#include "../Expression/Operator/Plus.h"
#include "../Expression/Operator/Minus.h"
#include "../Expression/Operator/Times.h"
#include "../Expression/Operator/Divide.h"

class Spreadsheet {
public:
    /**
     * Initializes graph of spreadsheet
     */
    Spreadsheet();

    /**
     * Save content of cell, given its coordinates from topLeft corner (e.g. {0,0})
     * @param coordinates
     * @param content
     */
    void saveCellContent(const Cell::Coord &coordinates, const std::string &content);

    /**
     * Save content of cell, given its address (e.g. A1)
     * @param address
     * @param content
     */
    void saveCellContentByAddress(const std::string &address, const std::string &content);

    /**
     * Delete all cells from spreadsheet
     */
    void clearSpreadsheet();

    /**
     * Get a cell contents using coordinates
     * @param coordinates
     * @return
     */
    std::string getCellContent(const Cell::Coord &coordinates) const;

    /**
     * Get display contents using coordinates (important for function cells, because contents contains actual formula)
     * @param coordinates
     * @return
     */
    std::string getCellDisplayContent(const Cell::Coord &coordinates) const;

    /**
     * Get cell pointer by address
     * @param address
     * @return
     */
    std::shared_ptr<Cell> getCellByAddress(const std::string &address) const;

    /**
     * Parse contents of function cell using shunting yard, operators and expressions
     * @param content
     * @param newCellAddress
     * @return
     */
    std::shared_ptr<FunctionCell>
    parseFunctionCellContent(const std::string &content, const std::string &newCellAddress);

    /**
     * Get all spreadsheet cells (used in export)
     * @return
     */
    std::map<std::string, std::shared_ptr<Cell>> getAllCells() const;

private:
    /**
     * Parse number expression (number, cell reference, function)
     * @param token
     * @param newCellAddress
     * @return
     */
    std::shared_ptr<DoubleExpression> parseExpression(const std::string &token, const std::string &newCellAddress);

    /**
     * Parse operator expression (Plus/Minus/Times/Divide)
     * @param token
     * @return
     */
    std::shared_ptr<OperatorExpression> static parseOperator(const std::string &token);

    /**
     * Create new cell for input content and address
     * @param content
     * @param newCellAddress
     * @return
     */
    std::shared_ptr<Cell> createCellFromContent(const std::string &content, const std::string &newCellAddress);

    /**
     * Main cells storage
     */
    std::map<std::string, std::shared_ptr<Cell>> cells;

    /**
     * Graph representing relations between cells
     */
    std::unique_ptr<Graph> graph;
};


#endif //SPREADSHEET_SPREADSHEET_H
