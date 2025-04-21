#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<set>

using namespace std;

/*
    [D]1. Split the input text into sentences using the period ('.') delimiter.

    [D]2. Convert each sentence to lowercase and remove punctuation.

    [D] 3. Tokenize sentences into words while filtering out stopwords.

    4. Count the frequency of each meaningful word using a map.

    5. Score each sentence based on the total frequency of its words.

    6. Sort sentences by score and select the top 30% for the summary.

    7. Reorder selected sentences to preserve their original sequence.

    8. Display the final summary to the user.
    */
   
set<string> stopwords = {"the", "is", "a", "an", "at", "to", "of", "and", "on"};

vector<string> tokenizeAndFilter(const string& s){
    vector<string> tokens;
    string word;
    stringstream ss(s);

    while(ss >> word){
        if(stopwords.find(word) == stopwords.end()){
            tokens.push_back(word);
        }
    }
    return tokens;
}

vector<string> splitToSentences(string text){
    //split a para into individual sentences (each ending with a '.')
    //stringstream converts string 'text' into a stream 'ss' to process it piece by piece
    vector<string> sents;
    stringstream ss(text);
    string sentence;
    
    while(getline(ss,sentence, '.')){ // extracts substrings from ss to sentence until it sees a '.'
        if(!sentence.empty()){
            sentence += '.';  // re-add the period to end of sentence
            sents.push_back(sentence);
        }
    }
    return sents;
}

string cleanNormalizeText(string sentence){
    string clean;
    for(char ch: sentence){
        if(isalpha(ch)||isspace(ch)){
            clean += tolower(ch);
        }
    }
    return clean;
}

//enter function to parse text
string parseText(string text){
    // split but append period
    // clean: lower, remove punctuation, tokenize
    // filter stopword
    // 
    
   vector<string> sentences = splitToSentences(text);
   
   //clean
   vector<vector<string>> tokens;

   for(string &s: sentences){
    s = cleanNormalizeText(s);      // returns clean lower case text
    tokens.push_back(tokenizeAndFilter(s));     // filters out stopwords and return token words
   }

   return "Parsing complete!";

}

string fileText(string f){
    ifstream file(f);
    string text, line;
    //add error handling here
    if(!file){
        cout << "\n\t Failed to open file..." << endl;
        return "\n";
    }
    while(getline(file, line)){
        text += line + " ";
    }
    file.close();
    return text;
}

void processText(string text){
    string parsed = parseText(text);
}

int menu(){
    int choice;
    cout << "\n\n===== T E X T\tS U M M A R I Z E R=====\n\n";
    cout << "\t1. Choose .txt file\n\t2. Enter text\n\t3. Exit\n\n";
    cout << "Enter choice:";
    cin >> choice;
    return choice;
}

int main(){
    cout << "Initializing my project!";
    int choice;
    string text, next;
    while(choice!=3){
        choice = menu();
        if(choice == 1){
            string filename;
            cout << "\n\tEnter TEXT file location: ";
            cin >> filename;
            text = fileText(filename);
        }else if(choice == 2){
            cout << "\n\t(If you're pasting, please press Ctrl+Shift+V)\n\tEnter text: ";
            cin.ignore();
            getline(cin, text);
        }else if(choice == 3){
            cout << "\n\n\n=== EXITING ===\n\n\n";
            break;
        }else{
            cout << "\nPlease enter 1 / 2 / 3\n\n";
        }
        cout << endl << endl << text << endl << endl;
        
        //function call to further: processText(text);
        
        
        /*
        To find summary of another text
        cout << "\n\n\tPress 3 to EXIT\n\tPress any other key to proceed to MENU";
        cin >> choice;
        */
       processText(text);
    }

    return 0;
}
