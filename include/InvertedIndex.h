#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "ConverterJSON.h"
#include <thread>
#include <mutex>
#include <fstream>
#include <string>

struct Entry {
    size_t doc_id, count;

    bool operator == (const Entry& other) const
    {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {

public:
    InvertedIndex() = default;
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);
    void createDictionary ();
    std::vector<std::string> refactorBloks (std::string InDocs);
    std::vector<Entry> GetWordCount(const std::string& word);
    void UpdateDocumentBaseFromFile(const std::vector<std::string>& fileNames);
    int docsCount();

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};
