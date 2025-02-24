
#ifndef SOCIALNETWORKPROJECT_UTILS_H
#define SOCIALNETWORKPROJECT_UTILS_H


#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Graph.h"
#include "Person.h"

std::vector<std::string> split(const std::string &s, char delimiter);

std::vector<int> parseIntList(const std::string &str);

std::vector<std::string> parseCsvLine(const std::string &line);

class Graph; // forward declaration of Graph

Graph readData(const std::string &filename);



#endif //SOCIALNETWORKPROJECT_UTILS_H
