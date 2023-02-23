#pragma once
#include <iostream>
#include <vector>
#include "InvertedIndex.h"

struct RelativeIndex
{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


class ConverterJSON {

public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();


    std::vector<std::string> GetRequests();


    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);


};
