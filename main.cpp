#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"



int main() {

    auto converterJSON = new ConverterJSON();
    auto invertedIndex = new InvertedIndex();


    auto getText = converterJSON->GetTextDocuments();

    invertedIndex->UpdateDocumentBase(getText);

    auto getRequest = converterJSON->GetRequests();

    invertedIndex->createDictionary();
/**
    invertedIndex->PrintDictionary();

*/
    auto server = new SearchServer(*invertedIndex);

    auto serchBase = server->search(converterJSON->GetRequests());

    converterJSON->putAnswers(serchBase);

    return 0;
}
