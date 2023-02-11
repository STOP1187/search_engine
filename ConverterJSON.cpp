#include <iostream>
#include <vector>
#include <fstream>
#include "ConverterJSON.h"
#include "nlohmann/json.hpp"


    std::vector<std::string> ConverterJSON::GetTextDocuments()
    {
        std::vector<std::string> base;
        std::ifstream fileConfig("config.json");

        if (!fileConfig)
        {
            std::cerr << "config file is missing" << std::endl;
        }
        else
        {
            nlohmann::json dict;
            fileConfig >> dict;
            base = dict["files"];
        }

        return base;
    };

    int ConverterJSON::GetResponsesLimit()
    {
        int maxResponses;
        std::ifstream fileConfig("config.json");

        if (!fileConfig)
        {
            std::cerr << "config file is missing" << std::endl;
        }
        else
        {
            nlohmann::json dict;
            fileConfig >> dict;
            maxResponses = dict["config"]["max_responses"];
        }
        fileConfig.close();

        return maxResponses;
    };

    std::vector<std::string> ConverterJSON::GetRequests()
    {
        std::vector<std::string> requests;
        std::ifstream fileRequest("requests.json");
        nlohmann::json dict;
        fileRequest >> dict;
        requests = dict["requests"];

        fileRequest.close();

        return requests;
    };



    void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
        std::ofstream fileAnswer("answers.json");
        nlohmann::json dict;
        bool result;
        auto converterJSON = new ConverterJSON();
        auto recodrRequest = converterJSON->GetRequests();

        for (int i = 0; i < answers.size(); ++i) {

            auto request = answers[i];


            for (int j = 0; j < request.size(); ++j) {

                if (answers[i][j].rank < 0)
                {
                    result = false;
                    dict = {
                            "answer", {
                                    {"request", recodrRequest[i]},
                                    {"result", result},
                            }
                    };


                    fileAnswer << dict << "," << std::endl;
                }
                else
                {
                    result = true;
                    dict = {
                            "answer", {
                                    {"request", recodrRequest[i]},
                                    {"result", result},
                                    {"relevance", {
                                            {"docid", answers[i][j].doc_id},
                                            {"rank", answers[i][j].rank}
                                    }}
                            }
                    };

                    fileAnswer << dict << "," << std::endl;
                }

            }

        }

        fileAnswer.close();
    };

