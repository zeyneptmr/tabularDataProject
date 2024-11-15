#include <iostream>
#include <new>
#include <stdexcept>

using namespace std;

char toUpperCase(char);
void displayMainMenu();
void clearConsole();
void returnToMainMenu();
bool handleUserSelection(char, bool&);
void newInfo();
void findInfo();
void listTable();

int main() {
    char choice;
    bool isRunning = true;

    while (isRunning) {
        displayMainMenu();
        cin >> choice;
        isRunning = handleUserSelection(choice, isRunning);
    }

    return 0;
}

void displayMainMenu() {
    cout << "Select an option: " << endl;
    cout << "A) New information entry" << endl;
    cout << "B) Find existing information with key" << endl;
    cout << "C) List current table" << endl;
    cout << "D) Exit" << endl;
    cout << "Your selection: ";
}

bool handleUserSelection(char choice, bool &isRunning) {
    switch (toUpperCase(choice)) {
        case 'A':
            newInfo();
            break;
        case 'B':
            findInfo();
            break;
        case 'C':
            listTable();
            break;
        case 'D':
           return false;
        default:
            clearConsole();
            cout << "Invalid option. Please make a valid choice!" << endl;    
    }
    return true;  
}

void newInfo() {
    clearConsole();
    cout << "New information entry." << endl;
    returnToMainMenu();  
}

void findInfo() {
    clearConsole();
    cout << "Find information." << endl;
    returnToMainMenu();  
}

void listTable() {
    clearConsole();
    cout << "Display current table." << endl;
    returnToMainMenu();  
}


char toUpperCase(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

void returnToMainMenu() {
    cout << "Press a button to the main menu." << endl;
    cin.ignore(); 
    cin.get();     
    clearConsole(); 
}


void clearConsole() {
    try {
        #ifdef _WIN32
            system("cls"); 
        #else
            cout << "\033[H\033[2J"; 
            cout.flush();
        #endif
    }
    catch (const exception& error) {
        cerr << "Error while clearing console: " << error.what() << endl;
    }
}


