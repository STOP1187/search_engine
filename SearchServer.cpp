#include "SearchServer.h"
#include "ConverterJSON.h"
#include <vector>
#include <string>


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{

    RelativeIndex relativeIndex;
    std::vector<std::vector<RelativeIndex>> baseAnswers;
    int sumCount = 0;
    float countMax = 0;
    std::vector<RelativeIndex> request;

    for (int i = 0; i < queries_input.size(); ++i)
    {
        auto req = _index.GetWordCount(queries_input[i]);

        for (int j = 0; j < req.size(); ++j)
        {

            relativeIndex.doc_id = req[j].doc_id;
            sumCount += req[j].count;


            if (req[j].count >= countMax)
            {
                countMax = req[j].count;
            }

            relativeIndex.rank = countMax / sumCount;
            request.push_back(relativeIndex);
        }

        if (!request.empty())
        {
            relativeIndex.doc_id = 0;
            relativeIndex.rank = -1;
            request.push_back(relativeIndex);

        }

        baseAnswers.push_back(request);

    }

    return baseAnswers;
};


