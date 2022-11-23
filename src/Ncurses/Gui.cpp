//
// Created by mikoun on 31.05.21.
//

#include <iostream>
#include "curses.h"
#include "Gui.h"

Gui::Gui(std::shared_ptr<Spreadsheet> spreadsheet) : spreadsheet(std::move(spreadsheet)) {
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        std::cout << "Your terminal does not support color\n";
        exit(1);
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color(); //starts colors
    curs_set(0); //hide cursor
    init_pair(1, COLOR_RED, COLOR_BLACK);
    renderSpreadsheet();
}


Gui::~Gui() {
    endwin();
}

void Gui::table() {
    int maxX, maxY, xOffset, yOffset;
    getmaxyx(stdscr, maxY, maxX);
    xOffset = LABELS_OFFSET;
    yOffset = LABELS_OFFSET;

    /** columns */
    for (int i = 0; i <= COLS_COUNT + 1; i++) {
        move(1, xOffset);
        vline(0, maxY - 1);
        xOffset += CELL_WIDTH;
    }

    /** rows */
    for (int i = 0; i <= ROWS_COUNT + 1; i++) {
        move(yOffset, 1);
        hline(0, maxX - 2);
        yOffset += CELL_HEIGHT;
    }

    for (int i = 0; i < COLS_COUNT; i++) {
        for (int j = 0; j < ROWS_COUNT; j++) {
            auto cellContent = spreadsheet->getCellDisplayContent({i, j});
            if (cellContent.length() > 15) {
                cellContent = cellContent.substr(0, 12).append("...");
            }
            mvprintw(
                    j * CELL_HEIGHT + LABELS_OFFSET + (CELL_HEIGHT >> 1),
                    i * CELL_WIDTH + LABELS_OFFSET + (CELL_WIDTH >> 1) - (cellContent.length() >> 1),
                    "%s",
                    cellContent.c_str()
            );
        }
    }

}

void Gui::renderSpreadsheet() {
    erase();
    table();
    labels();
    focusCell();
    refresh();
}

void Gui::focusCell() const {
    int x1 = fromLeft * CELL_WIDTH + LABELS_OFFSET, x2 = (fromLeft + 1) * CELL_WIDTH + LABELS_OFFSET;
    int y1 = fromTop * CELL_HEIGHT + LABELS_OFFSET, y2 = (fromTop + 1) * CELL_HEIGHT + LABELS_OFFSET;
    attrset(COLOR_PAIR(1));
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
    attroff(COLOR_PAIR(1));
}

void Gui::eraseCellContent() {
    spreadsheet->saveCellContent({fromLeft, fromTop}, "");
    renderSpreadsheet();
}

void Gui::editCell() {
    char cellBuffer[CELL_INPUT_BUFFER_SIZE];
    std::smatch matches;
    echo();
    curs_set(1);
    move(4, 10);
    clrtoeol();
    move(4, 10);
    std::string cellValue = spreadsheet->getCellContent({fromLeft, fromTop});
    for (int i = (int) (cellValue.length() - 1); i >= 0; i--) {
        ungetch(cellValue.at(i));
    }
    getnstr(cellBuffer, CELL_INPUT_BUFFER_SIZE);
    cellValue = cellBuffer;
    /** import from file command */
    if (std::regex_search(cellValue, matches, std::regex("^(\\!import)\\s([a-zA-Z]{1,20})$"))) {
        if (matches.size() == 3) {
            ImporterExporter::importFromFile(spreadsheet, matches[2]);
        }
    }
    /** export to file command */
    else if (std::regex_search(cellValue, matches, std::regex("^(\\!export)\\s([a-zA-Z]{1,20})$"))) {
        if (matches.size() == 3) {
            ImporterExporter::exportToFile(spreadsheet, matches[2]);
        }
    } else {
        spreadsheet->saveCellContent({fromLeft, fromTop}, cellValue);
    }
    noecho();
    curs_set(0);
    renderSpreadsheet();
}

void Gui::goRight() {
    if (fromLeft < COLS_COUNT) {
        fromLeft++;
    }
    renderSpreadsheet();
}

void Gui::goLeft() {
    if (fromLeft > 0) {
        fromLeft--;
    }
    renderSpreadsheet();
}

void Gui::goDown() {
    if (fromTop < COLS_COUNT) {
        fromTop++;
    }
    renderSpreadsheet();
}

void Gui::goUp() {
    if (fromTop > 0) {
        fromTop--;
    }
    renderSpreadsheet();
}

void Gui::labels() {
    for (int i = 0; i < COLS_COUNT + 1; i++) {
        mvprintw(0, (i + 1) * CELL_WIDTH - (CELL_WIDTH >> 1), "%c", Cell::colIndexToChar(i));
    }

    for (int i = 1; i < ROWS_COUNT + 1; i++) {
        mvprintw((i * CELL_HEIGHT) - (CELL_HEIGHT >> 1), 0, "%d", i);
    }
}
