//
// Created by mikoun on 27.05.21.
//

#ifndef SPREADSHEET_APP_H
#define SPREADSHEET_APP_H


#include <memory>
#include "curses.h"
#include "Core/Spreadsheet.h"
#include "Ncurses/Gui.h"

class App {
public:
    /**
     * Main app constructor, initializes spreadsheet object and GUI
     */
    App();

    /**
     * Main app method, contains infinite loop for catching key inputs to control ncurses GUI
     */
    void run();

private:
    /**
     * Main spreadsheet object pointer
     */
    std::shared_ptr<Spreadsheet> spreadsheet;

    /**
     * Gui object pointer
     */
    std::unique_ptr<Gui> gui;
};


#endif //SPREADSHEET_APP_H
