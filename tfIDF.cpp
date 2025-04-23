#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const set<string> STOPWORDS = {"the", "is", "a", "an", "at", "to", "of", "and", "on"};

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

void parseText(const string &text, vector<string> &sents, vector<vector<string>> &tokenized)
{
    sents = split(text);

    for (const string &s : sents)
    {
        string cleaned = clean(s);
        tokenized.push_back(tokenize(cleaned));
    }
}

// getSummary

// scoreSentences

// computeIDF(tokenized)
map<string, double> computeIDF(const vector<string> &tokenized)
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
    for(const auto &entry: docFreq){
        idf[entry.first] = log((double)total / entry.second);
    }
    return idf;
}

void summarizeText(const string &text)
{
    vector<string> sents;
    vector<vector<string>> tokenized;

    parseText(text, sents, tokenized);
    //  map<string, double> idf = computeIDF(tokenized);
    //  vector<pair<int,double>> scores = scoreSentences(tokenized, idf);
    //  vector<string> summary = getSummary(scores, sentences);

    cout << "\n\n===== S U M M A R Y =====\n\n";
    /*for(const string &s: summary){
        cout << "=> " << s << '\n';
    }*/
}

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

int menu()
{
    int choice;
    cout << "\n\n===== T E X T\tS U M M A R I Z E R=====\n\n";
    cout << "\t1. Choose .txt file\n\t2. Enter text\n\t3. Exit\n\n";
    cout << "Enter choice:";
    cin >> choice;
    return choice;
}

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
        // summarizeText(text);
    }

    cout << "\n\n\n=== EXITING ===\n\n\n";
    return 0;
}