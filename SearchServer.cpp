#include "SearchServer.h"
#include "ConverterJSON.h"
#include <vector>
#include <string>
#include <numeric>




std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> baseAnswers;
    int sumCount = 0;
    float countMax = 0;

    std::map<std::string, std::vector<Entry>> serchResult;

    for (int i = 0; i < queries_input.size(); ++i) {

        auto req = _index.GetWordCount(queries_input[i]);
        serchResult[queries_input[i]] = req;

        if (req.empty())
        {
            continue;
        }

        auto result = std::max_element(serchResult[queries_input[i]].begin(), serchResult[queries_input[i]].end(),
                                       [](Entry a, Entry b) {
                                           return a.count < b.count;
                                       });

        if (countMax < result->count)
        {
            countMax = result->count;
        }


    }

    for (int i = 0; i < queries_input.size(); ++i)
    {
        RelativeIndex relative;
        std::vector<RelativeIndex> request;


        for (int j = 0; j < serchResult[queries_input[i]].size(); ++j)
        {

            auto lambda = [&j](float a, std::pair<std::string , std::vector<Entry>> b)
            {if (!b.first.empty() && !b.second.empty() && b.second[j].doc_id == 0)
            {
                return a + b.second[j].count;
            }
                return a;
            };

            auto sumCount = std::accumulate(serchResult.begin(), serchResult.end(), 0.0f, lambda);


            relative.doc_id = serchResult[queries_input[i]][j].doc_id;
            relative.rank = sumCount / countMax;

            request.push_back(relative);

        }


        baseAnswers.push_back(request);
    }

    return baseAnswers;
};


