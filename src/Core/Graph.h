//
// Created by mikoun on 14.06.21.
//

#ifndef SPREADSHEET_GRAPH_H
#define SPREADSHEET_GRAPH_H

#include <map>
#include <set>
#include <string>

class Graph {
public:
    /**
     * Add edge to directed graph of dependecies
     * @param from nodeFrom
     * @param to nodeTo
     */
    void addEdge(const std::string &from, const std::string &to);

    /**
     * Get set of cells, which depend on my value to calculate theirs
     * @param me address of me
     * @return set of dependent cells
     */
    std::set<std::string> dependOnMeCells(const std::string &me);

    /**
     * When emptying cells, erase dependencies to avoid segfault while recalculating
     * @param address
     */
    void eraseCellDependencies(const std::string &address);

    /**
     * Detect cycle in directed graph
     * @return bool is cycle in graph
     */
    bool hasCycle() const;

    /**
     * Clears graph during import
     */
    void clear();

private:
    /**
     * Helper function for cycle detection
     * @param node
     * @param visited
     * @return
     */
    bool hasCycleOneNode(const std::string &node, std::set<std::string> &visited) const;

    /**
     * set of cells I depend on
     */
    std::map<std::string, std::set<std::string>> dependsOn;

    /**
     * set of cells, which depend on me while calculating their value
     */
    std::map<std::string, std::set<std::string>> dependOnMe;
};


#endif //SPREADSHEET_GRAPH_H
