//
// Created by mikoun on 27.05.21.
//

#include "App.h"


App::App() {
    spreadsheet = std::make_shared<Spreadsheet>();
    gui = std::make_unique<Gui>(spreadsheet);
}

void App::run() {
    gui->renderSpreadsheet();
    int key;
    while (true) {
        key = getch();
        switch (key) {
            case KEY_LEFT:
                gui->goLeft();
                break;
            case KEY_RIGHT:
                gui->goRight();
                break;
            case KEY_UP:
                gui->goUp();
                break;
            case KEY_DOWN:
                gui->goDown();
                break;
            case KEY_RESIZE:
                gui->renderSpreadsheet();
                break;
            case 10:
                gui->editCell();
                break;
            case KEY_DC:
                gui->eraseCellContent();
                break;
            case 27:
                return;
        }
    }
}
