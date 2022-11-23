//
// Created by mikoun on 15.06.21.
//

#ifndef SPREADSHEET_IMPORTEREXPORTER_H
#define SPREADSHEET_IMPORTEREXPORTER_H

#include <memory>
#include <fstream>
#include "Spreadsheet.h"

class ImporterExporter {
public:
    /**
     * Export spreadsheet to file, format is to be viewed in examples folder
     * @param spreadsheet
     * @param fileName
     */
    static void exportToFile(const std::shared_ptr<Spreadsheet>& spreadsheet, const std::string& fileName);

    /**
     * Import saved spreadsheet from file
     * @param spreadsheet
     * @param fileName
     */
    static void importFromFile(const std::shared_ptr<Spreadsheet>& spreadsheet, const std::string& fileName);
};


#endif //SPREADSHEET_IMPORTEREXPORTER_H
