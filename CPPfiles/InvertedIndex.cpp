#include "InvertedIndex.h"


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
    std::mutex access;


    for (int i = 0; i < docs.size(); ++i)
    {
        std::thread myThread ( [&] {

            auto blok = refactorBloks(docs[i]);

            for (int j = 0; j < blok.size(); ++j) {
                Entry entry;
                entry.doc_id = i;
                entry.count = 0;

                line = blok[j];

                for (int k = 0; k < blok.size(); ++k) {

                    if (line == blok[k]) {
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
        myThread.join();
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

using namespace std;
void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<vector<Entry>>& expected
) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
const vector<string> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the Great bell of the striking clock"
};
const vector<string> requests = {"london", "the"};
const vector<vector<Entry>> expected = {
        {
                {0, 1}
        }, {
                {0, 1}, {1, 3}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
const vector<string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
};
const vector<string> requests = {"milk", "water", "cappuchino"};
const vector<vector<Entry>> expected = {
        {
                {0, 4}, {1, 1}, {2, 5}
        }, {
                {0, 2}, {1, 2}, {2, 5}
        }, {
                {3, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
const vector<string> docs = {
        "a b c d e f g h i j k l",
        "statement"
};
const vector<string> requests = {"m", "statement"};
const vector<vector<Entry>> expected = {
        {
        }, {
                {1, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}



