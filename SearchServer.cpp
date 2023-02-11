#include "SearchServer.h"
#include "ConverterJSON.h"


    std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

        std::vector<std::vector<RelativeIndex>> base;

        RelativeIndex relativeIndex;

        int sumCount = 0;
        float countMax = 0;


        for (int i = 0; i < queries_input.size(); ++i)
        {
            auto req = _index.GetWordCount(queries_input[i]);


            std::vector<RelativeIndex> request;

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

            base.push_back(request);

        }

        return base;
    };


