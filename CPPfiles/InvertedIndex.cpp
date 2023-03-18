#include "InvertedIndex.h"


void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs)
{
    docs = input_docs;
    createDictionary();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    Entry entry{};
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
    std::mutex access;

    std::vector<std::thread> threads;

    for (int i = 0; i < docs.size(); ++i)
    {
        std::thread myThread ( [&] {

            auto blok = refactorBloks(docs[i]);

            for (int j = 0; j < blok.size(); ++j) {
                Entry entry{};
                entry.doc_id = i;
                entry.count = 0;

                line = blok[j];

                for (const auto & k : blok) {

                    if (line == k) {
                        entry.count += 1;
                    }
                }

                if (freq_dictionary.contains(line)) {
                    auto iter = std::find_if(freq_dictionary[line].begin(), freq_dictionary[line].end(), [&cm = entry]
                            (const Entry &m) -> bool { return cm.doc_id == m.doc_id; });

                    if (iter != std::end(freq_dictionary[line])) {
                        iter->count = entry.count;

                    } else {
                        access.lock();
                        freq_dictionary[line].push_back(entry);
                        access.unlock();
                    }


                } else {
                    access.lock();
                    freq_dictionary[line].push_back(entry);
                    access.unlock();
                }

            }

            wordCount.clear();
        });

        threads.push_back(std::move(myThread));

    }

    std::for_each(threads.begin(), threads.end(), [](std::thread &th)
    {
        th.join();
    });

}

std::vector<std::string> InvertedIndex::refactorBloks (std::string InDocs)
{
    std::vector<std::string> result;
    std::string word;

    for (int j = 0; j < InDocs.size(); ++j)
    {
        char symbol = InDocs[j];

        if (symbol == ' ' && !InDocs.empty())
        {
            result.push_back(word);
            word = "";
        }
        else if (symbol == ',' && !InDocs.empty())
        {
            result.push_back(word);
            word = "";
        }
        else if (symbol == '.' && !InDocs.empty())
        {
            result.push_back(word);
            word = "";
        }
        else
        {
            word += symbol;
        }
    }
    if (!word.empty())
    {
        result.push_back(word);
    }
    return result;
}

void InvertedIndex::UpdateDocumentBaseFromFile(const std::vector<std::string>& fileNames)
{
    for (const auto & input_doc : fileNames)
    {
        std::ifstream file(input_doc);
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