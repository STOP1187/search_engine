#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> baseAnswers;
    float relAbs = 0;
    std::map<std::string, std::vector<Entry>> serchResult;
    std::map<int, std::string, std::less<int>> dupsMap;

    for (const auto & i : queries_input) {

        auto words = this->_index.refactorBloks(i);

        sort(words.begin(), words.end() );

        words.erase(unique(words.begin(), words.end() ),words.end() );

        for (const auto &target: words)
        {
            int dups = std::count(words.begin(), words.end(), target);
            dupsMap[dups] = target;
        }

        std::vector<Entry> req;

        for (const auto & j : dupsMap)
        {
            auto reqResult = _index.GetWordCount(j.second);

            if (reqResult.empty())
            {
                continue;
            }

            auto maxResponse = reqResult.size() < _maxResponse ? reqResult.end() : reqResult.begin() + _maxResponse;

            req.insert(req.end(), reqResult.begin(), maxResponse);
        }

        serchResult[i] = req;

        float max = 0;
        for(int k = 1; k < serchResult[i].size(); k++)
        {
            max += serchResult[i][k].count;
        }

        if (relAbs < max)
        {
            relAbs = max;
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
            relative.rank = sumCount / relAbs;
            request.push_back(relative);
        }
        baseAnswers.push_back(request);
    }
    return baseAnswers;
}

