#include <iostream>
#include "gtest/gtest.h"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"




int main() {

    auto* converterJSON = new ConverterJSON();
    auto* invertedIndex = new InvertedIndex();

    auto getText = converterJSON->GetTextDocuments();
    invertedIndex->UpdateDocumentBase(getText);
    invertedIndex->createDictionary();

    auto* server = new SearchServer(*invertedIndex);

    auto getRequest = converterJSON->GetRequests();

    auto serchBase = server->search(getRequest);

    converterJSON->putAnswers(serchBase);

    delete converterJSON;
    delete invertedIndex;
    delete server;

    std::cout << "search completed" <<std::endl;
    return 0;
}
