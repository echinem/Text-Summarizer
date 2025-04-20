#include<iostream>
using namespace std;

//enter function to parse text

// enter function to extract text from file

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
    while(choice!=3){
        choice = menu();
        if(choice == 1){
            cout << "\n\tEnter TEXT file location: ";
        }else if(choice == 2){
            cout << "\n\tEnter text: ";
        }else if(choice == 3){
            cout << "\n\n\n=== EXITING ===\n\n\n";
            break;
        }else{
            cout << "\nPlease enter 1 / 2 / 3\n\n";
        }
    }
    return 0;
}