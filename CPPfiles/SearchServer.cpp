#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> baseAnswers;
    float countMax = 0;
    std::map<std::string, std::vector<Entry>> serchResult;

    for (const auto & i : queries_input) {

        auto words = this->_index.refactorBloks(i);
        std::vector<Entry> req;

        for (const auto & j : words)
        {
            auto reqResult = _index.GetWordCount(j);

            if (reqResult.empty())
            {
                continue;
            }
            req.insert(req.end(), reqResult.begin(), reqResult.end());
        }

        serchResult[i] = req;

        auto result = std::max_element(serchResult[i].begin(), serchResult[i].end(),
                                       [](Entry a, Entry b) {
                                           return a.count < b.count;
                                       });

        if (countMax < result->count)
        {
            countMax = result->count;
        }
    }

    for (const auto & i : queries_input)
    {
        RelativeIndex relative{};
        std::vector<RelativeIndex> request;

        for (int j = 0; j < serchResult[i].size(); ++j)
        {
            auto lambda = [&j](float a, std::pair<std::string , std::vector<Entry>> b)
            {if (!b.first.empty() && !b.second.empty())
            {
                return a + b.second[j].count;
            }
                return a;
            };

            auto sumCount = std::accumulate(serchResult.begin(), serchResult.end(), 0.0f, lambda);

            relative.doc_id = serchResult[i][j].doc_id;
            relative.rank = sumCount / countMax;
            request.push_back(relative);
        }
        baseAnswers.push_back(request);
    }
    return baseAnswers;
}

