#include "ConverterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::vector<std::string> massive;
    std::string file;
    std::ifstream fileConfig("config.json");

    if (!fileConfig)
    {
        throw ConfigNotFoundExeption();
    }

    nlohmann::json inList;
    fileConfig >> inList;
    massive = inList["files"];
    maxResponse = inList["config"]["max_responses"];

    fileConfig.close();

    return massive;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> requests;
    std::ifstream fileRequest("requests.json");

    if (!fileRequest)
    {
        throw RequestNotFoundExeption();
    }

    nlohmann::json dict;
    fileRequest >> dict;
    requests = dict["requests"];

    fileRequest.close();
    return requests;
}


void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers)
{
    std::ofstream fileAnswer("answers.json");
    nlohmann::json dict;

    if (!fileAnswer)
    {
        throw AnswersNotFoundExeption();
    }

    bool result;

    for (int i = 0; i < answers.size(); ++i)
    {
       auto request = answers[i];
       auto requestName = GetRequests()[i];

        if (answers[i].empty()) {
            result = false;
            dict = {
                    "answer", {
                            {"request", requestName},
                            {"result", result},
                    }
            };

            fileAnswer << dict << "," << std::endl;
            continue;
        }

       for (int j = 0; j < request.size(); ++j)
       {

           if (answers[i].empty())
           {
               result = false;
               dict = {
                       "answer", {
                               {"request", requestName},
                               {"result", result},
                       }
               };

           }
           else
           {
               result = true;
               dict = {
                       "answer", {
                               {"request", requestName},
                               {"result", result},
                               {"relevance", {
                                       {"docid", answers[i][j].doc_id},
                                       {"rank", answers[i][j].rank}
                               }}
                       }
               };


           }
           fileAnswer << dict << "," << std::endl;
       }

    }

    fileAnswer.close();
}


