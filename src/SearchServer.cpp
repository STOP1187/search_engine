#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> baseAnswers;
    float countMax = 0;
    std::map<std::string, std::vector<Entry>> serchResult;

    for (const auto & i : queries_input) {

        auto words = this->_index.refactorBloks(i);

        sort(words.begin(), words.end() );
        std::map<std::string, int, std::less<std::string>> dupsMap;
        for (const auto &target: words){

            int dups = std::count(words.begin(), words.end(), target);
            dupsMap[target] = dups;
        }

        words.erase(unique(words.begin(), words.end() ),words.end() );

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

        Entry max{};
        for(int k = 1; k < serchResult[i].size(); k++)
        {
            max = serchResult[i][k].count < serchResult[i][k-1].count ? serchResult[i][k-1] : serchResult[i][k];
        }

        if (countMax < max.count)
        {
            countMax = max.count;
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

