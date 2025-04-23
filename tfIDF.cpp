#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// summarizeText(text)
// readFile(filename)

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
            // text = readFile(filename);
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