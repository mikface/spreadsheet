//
// Created by mikoun on 15.06.21.
//

#include "ImporterExporter.h"

void ImporterExporter::exportToFile(const std::shared_ptr<Spreadsheet> &spreadsheet, const std::string &fileName) {
    std::ofstream exportFile;
    exportFile.open("exports/" + fileName);
    for (const auto &i:spreadsheet->getAllCells()) {
        exportFile << "{" << i.second->getAddress() << "}:\"" << i.second->value() << "\"" << std::endl;
    }
    exportFile.close();
}

void ImporterExporter::importFromFile(const std::shared_ptr<Spreadsheet> &spreadsheet, const std::string &fileName) {
    std::smatch matches;
    std::ifstream importFile("exports/" + fileName);
    std::string line, currentCellAddress, currentCellContent;
    spreadsheet->clearSpreadsheet();
    while (std::getline(importFile, line)) {
        if (std::regex_search(line, matches, std::regex("^\\{([A-Z](1[0-9]|2[0-5]|[1-9]))\\}\\:\\\"(.+)\\\"$"))) {
            if (matches.size() == 4) {
                spreadsheet->saveCellContentByAddress(matches[1].str(), matches[3].str());
            }
        }
    }
}
