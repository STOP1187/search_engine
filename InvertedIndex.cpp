#include "InvertedIndex.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "thread"
#include <mutex>



void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    for (int i = 0; i < input_docs.size(); ++i)
    {
        std::ifstream file(input_docs[i]);
        std::string line;
        std::string text;

        while (std::getline(file, line))
        {
            text += line + ' ';
        }
        docs.push_back(text);
        text = ' ';
        file.close();

    }

}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{

    Entry entry;
    entry.doc_id = 0;
    entry.count = 0;
    std::vector<Entry> plug;

    if (freq_dictionary.contains(word))
    {
        return freq_dictionary[word];
    }
    else
    {
        return plug;
    }
}


void InvertedIndex::createDictionary ()
{
    std::vector<Entry> wordCount;
    std::string line;

    for (int i = 0; i < docs.size(); ++i)
    {
        auto blok = refactorBloks(docs[i]);

        for (int j = 0; j < blok.size(); ++j)
        {
            Entry entry;
            entry.doc_id = i;
            entry.count = 0;

            line = blok[j];

            for (int k = 0; k < blok.size(); ++k)
            {

                if (line == blok[k])
                {
                    entry.count += 1;
                }


            }

            if (freq_dictionary.contains(line))
            {
                auto iter = std::find_if(freq_dictionary[line].begin(), freq_dictionary[line].end(), [&cm = entry]
                        (const Entry& m) -> bool { return cm.doc_id == m.doc_id;});

                if (iter != std::end(freq_dictionary[line]))
                {
                    iter->count = entry.count;

                }
                else
                {
                    freq_dictionary[line].push_back(entry);
                }


            }
            else
            {
                freq_dictionary[line].push_back(entry);
            }

        }

        wordCount.clear();

    }

}

std::vector<std::string> InvertedIndex::refactorBloks (std::string InDocs)
{
    std::vector<std::string> result;
    std::string word;
    char symbol;


    for (int j = 0; j < InDocs.size(); ++j)
    {
        symbol = InDocs[j];

        if (symbol == ' ' && InDocs.size() != 0)
        {
            result.push_back(word);
            word = "";
            symbol = 0;
        }
        else if (symbol == ',' && InDocs.size() != 0)
        {
            result.push_back(word);
            word = "";
            symbol = 0;
        }
        else if (symbol == '.' && InDocs.size() != 0)
        {
            result.push_back(word);
            word = "";
            symbol = 0;
        }
        else
        {
            word += symbol;

        }
    }

    return result;
}





