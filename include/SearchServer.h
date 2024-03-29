#pragma once
#include <iostream>
#include <vector>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include <string>
#include <numeric>

class SearchServer {

public:
    SearchServer(InvertedIndex& idx) : _index(idx), _maxResponse(5){ };
    SearchServer(InvertedIndex& idx, int maxResponse) : _index(idx), _maxResponse(maxResponse){ };
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);

private:
    InvertedIndex _index;
    int _maxResponse;
};