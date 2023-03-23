#pragma once
#include <iostream>
#include <vector>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include <string>
#include <numeric>

class SearchServer {

public:
    SearchServer(InvertedIndex& idx) : _index(idx){ };
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);

private:
    InvertedIndex _index;
};