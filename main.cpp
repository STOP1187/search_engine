#include <iostream>
#include "gtest/gtest.h"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"




int main() {

    auto* converterJSON = new ConverterJSON();
    auto* invertedIndex = new InvertedIndex();
    auto* server = new SearchServer(*invertedIndex);

    auto getText = converterJSON->GetTextDocuments();

    invertedIndex->UpdateDocumentBase(getText);

    auto getRequest = converterJSON->GetRequests();

    invertedIndex->createDictionary();

    auto serchBase = server->search(getRequest);

    converterJSON->putAnswers(serchBase);

    delete converterJSON;
    delete invertedIndex;
    delete server;

    std::cout << "search completed" <<std::endl;
    return 0;
}
