//
// Created by mikoun on 14.06.21.
//

#include "Graph.h"

void Graph::addEdge(const std::string &from, const std::string &to) {
    /** for cycle detection */
    auto it = dependsOn.find(from);
    if (it == dependsOn.end()) {
        it = dependsOn.insert(std::map<std::string, std::set<std::string>>::value_type(from, {})).first;
    }

    if (it->second.find(to) == it->second.end()) {
        it->second.insert(to);
    }

    /** reversed for cell refreshing */
    auto it2 = dependOnMe.find(to);
    if (it2 == dependOnMe.end()) {
        it2 = dependOnMe.insert(std::map<std::string, std::set<std::string>>::value_type(to, {})).first;
    }

    if (it2->second.find(from) == it2->second.end()) {
        it2->second.insert(from);
    }
}

std::set<std::string> Graph::dependOnMeCells(const std::string &me) {
    auto it = dependOnMe.find(me);
    if (it == dependOnMe.end()) {
        return {};
    }
    return it->second;
}

void Graph::eraseCellDependencies(const std::string &erasedCellAddress) {
    auto it = dependsOn.find(erasedCellAddress);
    if (it != dependsOn.end()) {
        for (const auto &i:it->second) {
            dependOnMe.find(i)->second.erase(erasedCellAddress);
        }
        dependsOn.erase(erasedCellAddress);
    }
}

bool Graph::hasCycle() const {
    for (const auto &i:dependsOn) {
        std::set<std::string> visited = {};
        visited.insert(i.first);
        if (hasCycleOneNode(i.first, visited)) {
            return true;
        }
    }
    return false;
}

bool Graph::hasCycleOneNode(const std::string &node, std::set<std::string> &visited) const {
    if (dependsOn.find(node) == dependsOn.end()) {
        return false;
    }
    for (const auto &i: dependsOn.find(node)->second) {
        if (visited.find(i) != visited.end()) {
            return true;
        }
        visited.insert(i);
        if (hasCycleOneNode(i, visited)) {
            return true;
        }
        visited.erase(i);
    }

    return false;
}

void Graph::clear() {
    dependsOn.clear();
    dependOnMe.clear();
}

