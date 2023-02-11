#pragma once
#include <iostream>
#include <vector>
#include <map>

struct Entry {
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator == (const Entry& other) const
    {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {

public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> input_docs);

    void createDictionary ();

    std::vector<std::string> refactorBloks (std::string InDocs);

    void PrintDictionary ();

    std::vector<Entry> GetWordCount(const std::string& word);


private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь

};
