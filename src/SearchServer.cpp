#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{

    std::vector<std::vector<RelativeIndex>> baseAnswers;
    float relAbsMax = 0;
    std::map<std::string, std::vector<Entry>> serchResult;

    for (const auto & i : queries_input) {

        auto words = this->_index.refactorBloks(i);

        sort(words.begin(), words.end());

        words.erase(unique(words.begin(), words.end()),words.end());
        std::map<std::string, int, std::less<std::string>> dupsMap;

        for (const auto &target: words)
        {
            int dups = std::count(words.begin(), words.end(), target);
            dupsMap[target] = dups;
        }

        std::vector<Entry> req;

        for (const auto & j : dupsMap)
        {
            auto reqResult = _index.GetWordCount(j.first);

            if (reqResult.empty())
            {
                continue;
            }

            req.insert(req.end(), reqResult.begin(), reqResult.end());
        }

        serchResult[i] = req;

        for(int k = 0; k < _index.docsCount(); k++)
        {
            float max = 0;

            for (const auto & r : serchResult[i])
            {
                if (r.doc_id == k)
                {
                    max += r.count;
                }

                if (relAbsMax < max)
                {
                    relAbsMax = max;
                }
            }
        }
    }

    for (const auto & i : queries_input)
    {
        RelativeIndex relative{};
        std::vector<RelativeIndex> request;

        for (int j = 0; j < serchResult[i].size(); ++j)
        {
            auto relAbsForOneDocs = 0;

            float maxOneDocs = 0;

            for (const auto & r : serchResult[i])
            {
                if (r.doc_id == serchResult[i][j].doc_id)
                {
                    maxOneDocs += r.count;

                    if (relAbsForOneDocs < maxOneDocs)
                    {
                        relAbsForOneDocs = maxOneDocs;
                    }
                }
            }

            relative.doc_id = serchResult[i][j].doc_id;
            relative.rank = relAbsForOneDocs / relAbsMax;
            request.push_back(relative);
        }

        auto cmp = [](RelativeIndex const & a, RelativeIndex const & b)
        {
            return a.rank > b.rank;
        };
        std::sort(request.begin(), request.end(), cmp);

        auto maxResponse = request.size() < _maxResponse ? request.end() : request.begin() + _maxResponse;

        std::vector<RelativeIndex> finalRequest;

        finalRequest.insert(finalRequest.begin(), request.begin(), maxResponse);

        baseAnswers.push_back(finalRequest);
    }

    return baseAnswers;
}

