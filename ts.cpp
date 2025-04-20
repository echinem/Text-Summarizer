#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//enter function to parse text

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

    }
    return 0;
}
