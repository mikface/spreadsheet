//
// Created by mikoun on 31.05.21.
//

#ifndef SPREADSHEET_GUI_H
#define SPREADSHEET_GUI_H

#include "../Core/Spreadsheet.h"
#include "../Core/ImporterExporter.h"

#define COLS_COUNT 10
#define ROWS_COUNT 10
#define CELL_WIDTH 16
#define CELL_HEIGHT 4
#define LABELS_OFFSET 1
#define CELL_INPUT_BUFFER_SIZE 50

class Gui {
public:
    /**
     * Constructor initializes GUI, , sets color pairs for highlighting current position and renders spreadsheet
     * @param spreadsheet
     */
    explicit Gui(std::shared_ptr<Spreadsheet> spreadsheet);

    /**
     * Gui destructor
     */
    ~Gui();

    /**
     * Renders table of spreadsheet, firstly erases old screen, draws cells with contents and labels and current cell focus
     */
    void renderSpreadsheet();

    /**
     * Erases contents from current cell
     */
    void eraseCellContent();

    /**
     * Edits contents of current cell. Shows command line which can be used also for commands (!export/!import)
     */
    void editCell();

    /**
     * Go one cell right
     */
    void goRight();

    /**
     * Go one cell left
     */
    void goLeft();

    /**
     * Go one cell down
     */
    void goDown();

    /**
     * Go one cell up
     */
    void goUp();

private:

    /**
     * Renders grid and contents of cells
     */
    void table();

    /**
     * Renders labels of cells (letters horizontally, numbers vertically)
     */
    static void labels();

    /**
     * Renders colored focus onto current cell
     */
    void focusCell() const;

    /**
     * Current cell position from top
     */
    int fromTop = 0;

    /**
     * Current cell position from left
     */
    int fromLeft = 0;

    /**
     * Spreadsheet pointer, used for showing the contents of cells and updating cells
     */
    std::shared_ptr<Spreadsheet> spreadsheet;
};


#endif //SPREADSHEET_GUI_H
