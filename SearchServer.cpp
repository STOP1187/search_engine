#include "SearchServer.h"
#include "ConverterJSON.h"
#include <vector>
#include <string>
#include <numeric>
#include "gtest/gtest.h"



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
            {if (!b.first.empty() && !b.second.empty())
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

using namespace std;

TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}
TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const vector<string> request = {"moscow is the capital of russia"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.666666687},
                    {1, 0.666666687},
                    {2, 0.666666687}
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}
