#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {

    auto* converterJSON = new ConverterJSON();
    auto* invertedIndex = new InvertedIndex();

    try
    {
        auto getText = converterJSON->GetTextDocuments();
        invertedIndex->UpdateDocumentBaseFromFile(getText);
        invertedIndex->createDictionary();

        auto* server = new SearchServer(*invertedIndex);
        auto getRequest = converterJSON->GetRequests();
        auto serchBase = server->search(getRequest);

        converterJSON->putAnswers(serchBase);

        delete server;
    }
    catch (const std::exception& x)
    {
        std::cerr << x.what() << std::endl;
    }

    delete converterJSON;
    delete invertedIndex;

    std::cout << "search completed" <<std::endl;
    return 0;
}
