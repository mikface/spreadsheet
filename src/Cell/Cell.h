//
// Created by mikoun on 26.03.21.
//

#ifndef SPREADSHEET_CELL_H
#define SPREADSHEET_CELL_H
#define MAX_COL 20
#define MAX_ROW 20

#include <string>
#include <memory>
#include <set>

class Cell {
public:
    /**
     * Helper struct for cell coordinates from topLeft corner
     */
    struct Coord {
        Coord();

        Coord(int fromLeftVal, int fromTopVal);

        /**
         * Cells from left
         */
        int fromLeft;


        /**
         * Cells from top
         */
        int fromTop;
    };

    /**
     * Initializes cell with its content
     * @param content
     */
    explicit Cell(std::string content);

    /**
     * Needed for polymorphism
     */
    virtual ~Cell() = default;

    /**
     * Returns contents of the cell
     * @return
     */
    virtual std::string value() const;


    /**
     * Returns display contents of the cell (important for FunctionCell)
     * @return
     */
    virtual std::string displayValue() const;

    /**
     * Set address of the cell
     * @param newAddress
     */
    void setAddress(const std::string &newAddress);

    /**
     * Get the cell address
     * @return
     */
    std::string getAddress() const;

    /**
     * Convert coordinates to cell address
     * @param coordinates
     * @return
     */
    static std::string coordToAddress(const Cell::Coord &coordinates);

    /**
     * Helper function to convert cell address from coordinates (A = 0, B = 1...)
     * @param column
     * @return
     */
    static char colIndexToChar(int column);

protected:
    /**
     * Cell address
     */
    std::string address;
    /**
     * Cell content (formula for FunctionCell)
     */
    std::string content;
};


#endif //SPREADSHEET_CELL_H
