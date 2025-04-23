#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

const set<string> STOPWORDS = {
    "the", "is", "a", "an", "at", "to", "of", "and", "on",
    "in", "for", "with", "this", "that", "by", "from", "as",
    "are", "was", "were", "be", "been", "has", "have", "had",
    "it", "its", "not", "but", "or", "if", "then", "so", "do",
    "does", "did", "can", "could", "would", "should", "will",
    "may", "might", "must", "shall", "i", "we", "you", "he",
    "she", "they", "them", "his", "her", "their", "our", "my",
    "me", "your", "yours", "ours", "what", "which", "who",
    "whom", "how", "when", "where", "why", "also", "about",
    "all", "any", "some", "such", "no", "nor", "than", "too",
    "very"};

// for parsing text
vector<string> split(const string &text)
{
    vector<string> sents;
    stringstream ss(text);
    string sentence;

    while (getline(ss, sentence, '.'))
    {
        if (!sentence.empty())
        {
            sentence += '.';
            sents.push_back(sentence);
        }
    }
    return sents;
}

string clean(const string &sentence)
{
    string clean;
    for (char ch : sentence)
    {
        if (isalpha(ch) || isspace(ch))
        {
            clean += tolower(ch);
        }
    }
    return clean;
}

vector<string> tokenize(const string &text)
{
    vector<string> tokens;
    stringstream ss(text);
    string word;

    while (ss >> word)
    {
        if (STOPWORDS.find(word) == STOPWORDS.end())
        {
            // word isn't a stopword
            tokens.push_back(word);
        }
    }
    return tokens;
}

void parseText(const string &text, vector<string> &sents, vector<vector<string>> &tokenized)
{
    sents = split(text);

    for (const string &s : sents)
    {
        string cleaned = clean(s);
        tokenized.push_back(tokenize(cleaned));
    }
}

// for computing IDF
map<string, double> computeIDF(const vector<vector<string>> &tokenized)
{
    map<string, int> docFreq;
    for (const auto &s : tokenized)
    {
        set<string> unique(s.begin(), s.end());
        for (const string &word : unique)
        {
            docFreq[word]++;
        }
    }

    int total = tokenized.size();
    map<string, double> idf;
    for (const auto &entry : docFreq)
    {
        idf[entry.first] = log((double)total / entry.second);
    }
    return idf;
}

vector<pair<int, double>> scoreSentences(const vector<vector<string>> &tokenized, const map<string, double> &idf)
{
    vector<pair<int, double>> scores;

    for (int i = 0; i < tokenized.size(); i++)
    {
        map<string, int> tf;
        for (const string &word : tokenized[i])
        {
            tf[word]++;
        }

        double score = 0.0;
        for (auto it = tf.begin(); it != tf.end(); ++it) {
            const string& word = it->first;
            int freq = it->second;
            if (idf.count(word)) {
                score += freq * idf.at(word);
            }
        }
        scores.emplace_back(i, score);
    }
    return scores;
}

vector<string> getSummary(const vector<pair<int, double>> &scores, const vector<string> &sents, double ratio = 0.3)
{
    vector<pair<int, double>> sortedScores = scores;

    sort(sortedScores.begin(), sortedScores.end(), [](auto &a, auto &b)
         { return a.second > b.second; });

    int top = ceil(sortedScores.size() * ratio);
    vector<int> ind;

    for (int i = 0; i < top; i++)
    {
        ind.push_back(sortedScores[i].first);
    }

    sort(ind.begin(), ind.end());

    vector<string> summary;
    for (int i : ind)
    {
        summary.push_back(sents[i]);
    }

    return summary;
}

// controller function
void summarizeText(const string &text)
{
    vector<string> sents;
    vector<vector<string>> tokenized;

    parseText(text, sents, tokenized);
    map<string, double> idf = computeIDF(tokenized);
    vector<pair<int, double>> scores = scoreSentences(tokenized, idf);
    vector<string> summary = getSummary(scores, sents);

    cout << "\n\n===== S U M M A R Y =====\n\n";
    for (const string &s : summary)
    {
        cout << "=> " << s << '\n';
    }
}

// file handling
string readFile(const string &filename)
{
    ifstream file(filename);
    string text, line;

    if (!file)
    {
        cerr << "\n\tFailed to open file.\n";
        return "";
    }

    while (getline(file, line))
    {
        text += line + " ";
    }

    return text;
}

// user interaction
int menu()
{
    int choice;
    cout << "\n\n===== T E X T\tS U M M A R I Z E R=====\n\n";
    cout << "\t1. Choose .txt file\n\t2. Enter text\n\t3. Exit\n\n";
    cout << "Enter choice:";
    cin >> choice;
    return choice;
}

// main entry point
int main()
{
    int choice;
    string text;

    while ((choice = menu()) != 3)
    {
        cin.ignore();

        if (choice == 1)
        {
            string filename;
            cout << "\n\tEnter path to TXT file: ";
            getline(cin, filename);
            text = readFile(filename);
        }
        else if (choice == 2)
        {
            cout << "\n\tEnter text: \n";
            getline(cin, text);
        }
        else
        {
            cout << "\nInvalid choice. Please enter 1, 2 or 3.\n";
            continue;
        }

        cout << "\nOriginal Text: \n"
             << text << endl;
        summarizeText(text);
    }

    cout << "\n\n\n=== EXITING ===\n\n\n";
    return 0;
}