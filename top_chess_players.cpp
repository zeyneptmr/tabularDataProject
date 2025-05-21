#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <new>
#include <fstream>
#include <algorithm>
using namespace std;

const int maxSize = 3; // initial size of the array

// Player class 
class Player {
private:
    string name;
    string surname;
    string nationality;
    int ranking;
    int rating;
    int birthYear;
    int fideID;

public:
    // Constructor
    Player();

    // Getter and Setter methods
    string getName() const;
    string getSurname() const;
    string getNationality() const;
    int getRanking() const;
    int getRating() const;
    int getBirthYear() const;
    int getFIDEID() const;

    void setName(const string& playerName);
    void setSurname(const string& playerSurname);
    void setNationality(const string& playerNationality);
    void setRanking(int playerRanking);
    void setRating(int playerRating);
    void setBirthYear(int playerBirthYear);
    void setFIDEID(int playerFIDEID);
    
    // Methods to manage players
    void expandArray();
    void display() const; 
    void editSingleRow(); //Method to edit information of specific player
    void deleteRow(); //Method to delete information of specific player
    void insertNewRow(); //Method to insert new player 
    void displayRow(); //Method to display information of specific player
    void displayTable(); //Method to display table

};

// Create single dynamic array of object
int countEntry = 0;
int arraySize = maxSize;
Player* players = new Player[arraySize];

// Function prototypes
int findRow(int playerFIDEID); // Function to find player by FIDE ID
bool checkFIDEID(const Player* players, int countEntry, int fideID); //Check players FIDEID, returns false  if same FIDE ID is entered second time
bool handleUserSelection(int choice); // Function to handle user's selection and perform corresponding actions
bool getValidateString(string &input); // Checks if the string is valid
bool getValidateNumber(int &number);   // Checks if the number is valid

void clearConsole();

int main() {
    int choice;
    while (handleUserSelection(choice));

    delete[] players; // Free dynamically allocated memory
    players = nullptr;
    return 0;
}

// Constructor to initialize player attributes
Player::Player() { //constructor
    name = "";
    surname = "";
    nationality = "";
    ranking = 0;
    rating = 0;
    birthYear = 0;
    fideID = 0;
}

// Getter methods
string Player::getName() const { 
    return name; 
}

string Player::getSurname() const { 
    return surname; 
}

string Player::getNationality() const { 
    return nationality; 
}

int Player::getRanking() const { 
    return ranking; 
}

int Player::getRating() const { 
    return rating; 
}

int Player::getBirthYear() const { 
    return birthYear; 
}

int Player::getFIDEID() const { 
    return fideID; 
}

//Setter methods
void Player::setName(const string& playerName) {
    name = playerName; 
}

void Player::setSurname(const string& playerSurname) { 
    surname = playerSurname; 
}

void Player::setNationality(const string& playerNationality) {
    nationality = playerNationality; 
}

void Player::setRanking(int playerRanking) { 
    ranking = playerRanking; 
}

void Player::setRating(int playerRating) { 
    rating = playerRating; 
}

void Player::setBirthYear(int playerBirthYear) { 
    birthYear = playerBirthYear; 
}

void Player::setFIDEID(int playerFIDEID) { 
    fideID = playerFIDEID; 
}

// Display player information in a formatted table
void Player::display() const { 
    cout << left;
    cout << setw(15) << name
         << setw(15) << surname
         << setw(15) << nationality
         << setw(10) << ranking
         << setw(10) << rating
         << setw(15) << birthYear
         << setw(10) << fideID << endl;
}

// Function to check if the FIDE ID already exists
bool checkFIDEID(Player players[], int countEntry, int playerID) {
    for (int i = 0; i < countEntry; i++) {
        if (playerID == players[i].getFIDEID()) { // Check if the FIDE ID already exists
            cout << "This FIDE ID already exists. Players cannot have the same FIDE ID.\n";
            return false;
        }
    }
    return true;
}
 
// Method to edit specific player's information
void Player::editSingleRow() {
    int choice;
    string tempString;
    int tempNumber;

    while (true) {
        cout << "\nSelect an option to edit (1-7):\n";
        cout << "1. Name\n";
        cout << "2. Surname\n";
        cout << "3. Nationality\n";
        cout << "4. Ranking\n";
        cout << "5. Rating\n";
        cout << "6. Birth Year\n";
        cout << "7. FIDE ID\n";
        cout<<"Please make a choice (press 0 to exit): ";
        
        if (!getValidateNumber(choice)) // Checks the validation of number entered
            return;

        switch (choice) {
        case 1:
            while (true) {
                cout << "\nPlease enter new Name: ";
                cin.ignore();
                if (getValidateString(tempString)) {
                    setName(tempString);
                    break;
                }
            }
            break;

        case 2:
            while (true) {
                cout << "\nPlease enter new Surname: ";
                cin.ignore();
                if (getValidateString(tempString)) {
                    setSurname(tempString);
                    break;
                }
            }
            break;

        case 3:
            while (true) {
                cout << "\nPlease enter new Nationality: ";
                cin.ignore();
                if (getValidateString(tempString)) {
                    setNationality(tempString);
                    break;
                }
            }
            break;

        case 4:
            while (true) {
                cout << "\nPlease enter new Ranking: ";
                if (getValidateNumber(tempNumber)) {
                    setRanking(tempNumber);
                    break;
                }
            }
            break;

        case 5:
            while (true) {
                cout << "\nPlease enter new Rating: ";
                if (getValidateNumber(tempNumber)) {
                    setRating(tempNumber);
                    break;
                }
            }
            break;

        case 6:
            while (true) {
                cout << "\nPlease enter new Birth Year: ";
                if (getValidateNumber(tempNumber)) {
                    setBirthYear(tempNumber);
                    break;
                }
            }
            break;

        case 7:
            while (true) {
                cout << "\nPlease enter new FIDE ID: ";
                if (getValidateNumber(tempNumber)) {
                    if (checkFIDEID(players, countEntry, tempNumber)) { 
                        setFIDEID(tempNumber); 
                        break;
                    }
                }
            }
            break;

        case 0:
            return;

        default:
            cout << "Invalid choice, please make a valid choice (1-7).\n";
        }
    }
    cout << "**Player information updated succesfully**\n";
}

// Method to delete a specific player's information
void Player::deleteRow() {
    int playerIndex = findRow(fideID); 
    
    if (playerIndex != -1) {
        for (int i = playerIndex; i < countEntry - 1; ++i) {
            players[i] = players[i + 1];  // Shift all players one position up
        }
        countEntry--;  
        cout << "\n**Player deleted successfully!**\n";
    } else {
        cout << "Player not found!\n";
    }
}

// Expand the player array when the maximum size is reached
void expandArray() {
    arraySize *= 2;
    Player* tempPlayers = new (nothrow) Player[arraySize]; // Allocate a new dynamic array of Player objects with a size of 'arraySize'
    
    // Check if memory allocation for the new array was successful
    if(tempPlayers != nullptr){
        for (int i = 0; i < countEntry; i++) { // Copy the existing players from the old array into the new, larger array
            tempPlayers[i] = players[i];
        }
        delete[] players; // Deallocate the old array to free up memory

        players = tempPlayers; // Point 'players' to the newly expanded array
        cout << "\n**Array expanded successfully!**\n";
        cout<<"New size of array = " << arraySize << "\n\n";
    }
    else
    {
        cerr << "Memory allocation failed! Array could not be expanded \n";
        return; 
    }
}

// Insert a new player information into the table
void insertNewRow() {
    if (countEntry >= arraySize) {
        expandArray();
    }

    Player* newPlayer = new Player(); // Dynamically allocate memory for a new Player object using the default constructor.
    string tempString;
    int tempNumber;

    cin.ignore();

    while (true) {
        cout << "Please enter Player's Name: ";
        if (getValidateString(tempString)){
            newPlayer->setName(tempString);
            break;
        }
    }

    while (true) {
        cout << "Please enter Player's Surname: ";
        if (getValidateString(tempString)){
            newPlayer->setSurname(tempString);
            break;
        }
    }

    while (true) {
        cout << "Please enter Player's Nationality: ";
        if (getValidateString(tempString)){
            newPlayer->setNationality(tempString);
            break;
        }
    }

     while (true) {
        cout << "Please enter Player's Ranking: ";
        if (getValidateNumber(tempNumber)){
            newPlayer->setRanking(tempNumber);
            break;
        }
    }

    while (true) {
        cout << "Please enter Player's Rating: ";
        if (getValidateNumber(tempNumber)){
            newPlayer->setRating(tempNumber);
            break;
        }
    }

    while (true) {
        cout << "Please enter Player's Birth Year: ";
        if (getValidateNumber(tempNumber)){
            newPlayer->setBirthYear(tempNumber);
            break;
        }
    }

    while (true) {
        cout << "Please enter Player's FIDE ID: ";
        if (getValidateNumber(tempNumber)) {
            if (checkFIDEID(players, countEntry, tempNumber)) {  // Check if the FIDE ID already exists
                newPlayer->setFIDEID(tempNumber); // Set FIDE ID if it's valid
                break;
            }
        }
    }

    players[countEntry] = *newPlayer; // Copy the contents of the newly created Player object (pointed to by 'newPlayer')
    countEntry++;
    cout << "\n**Player added successfully**\n";
    
    delete newPlayer; // Deallocate the dynamically allocated memory for 'newPlayer'.
}

// Find a player by their FIDE ID
int findRow(int playerFIDEIDToFind) {
    for (int i = 0; i < countEntry; i++) {
        if (players[i].getFIDEID() == playerFIDEIDToFind) { // Compare player's FIDE ID
            return i;
        }
    }
    return -1;
}

// Function to load data from file
void loadFromFile() {
    string filename;
    cout << "Enter the file name to load data: ";
    cin >> filename;

    // Opens the file in read mode
    ifstream inFile(filename);

    // Checks if the file was successfully opened
    if (!inFile) {
        cerr << "Error! File could not be opened!\n";
        return;
    }
    //Initializes the countEntry variable to 0 to start reading the data from the file
    countEntry = 0;

    // Reads the file line by line until the end
    while (!inFile.eof()) {

        // Checks if the array is full and if its full, expands the array
        if (countEntry > arraySize) {
            expandArray();
        }
        Player newPlayer; // new Player object to store the data for the player being read from the file
        string tempString; // Temporary string variable to hold data read from the file
        int tempNumber; // Temporary integer variable to hold numeric data read from the file
        
        // Read player data from file and set the corresponding player attributes
        inFile >> tempString; // player Name
        if (tempString.empty()) break; // Stop if Name is empty which means end of data
        newPlayer.setName(tempString);

        inFile >> tempString; //read player Surname
        newPlayer.setSurname(tempString); 

        inFile >> tempString; // read players Nationality
        newPlayer.setNationality(tempString);

        inFile >> tempNumber; // read players Ranking
        newPlayer.setRanking(tempNumber);

        inFile >> tempNumber; // read players Rating
        newPlayer.setRating(tempNumber);

        inFile >> tempNumber; // read players Birth Year
        newPlayer.setBirthYear(tempNumber);

        inFile >> tempNumber; // read players FIDE ID
        newPlayer.setFIDEID(tempNumber);

        // Add the newly player to the array
        players[countEntry++] = newPlayer;
    }

    inFile.close();
    cout << "**Data loaded successfully**\n";
}

// save listed data to txt file
void saveToFile() {
    string filename;
    cout << "Enter the file name to save data: ";
    cin >> filename;
    // Open the file for writing
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error! File could not be opened!\n";
        return;
    }
    // Loop through all players and write their details to the file
    for (int i = 0; i < countEntry; i++) {
        outFile << players[i].getName() << " "
                << players[i].getSurname() << " "
                << players[i].getNationality() << " "
                << players[i].getRanking() << " "
                << players[i].getRating() << " "
                << players[i].getBirthYear() << " "
                << players[i].getFIDEID() << "\n";
    }

    outFile.close();
    cout << "**Data saved successfully**\n";
}

// compare two players by name for sorting -alphabetical order
bool compareByName(const Player &a, const Player &b) {
    return a.getName() < b.getName();
}
// Compare by surname
bool compareBySurname(const Player &a, const Player &b) {
    return a.getSurname() < b.getSurname();
}
// Compare by nationality
bool compareByNationality(const Player &a, const Player &b) {
    return a.getNationality() < b.getNationality();
}
// Compare by ranking 
bool compareByRanking(const Player &a, const Player &b) {
    return a.getRanking() < b.getRanking();
}
// Compare by rating 
bool compareByRating(const Player &a, const Player &b) {
    return a.getRating() < b.getRating();
}
// Compare by birth year
bool compareByBirthYear(const Player &a, const Player &b) {
    return a.getBirthYear() < b.getBirthYear();
}
// Compare by fide id
bool compareByFIDEID(const Player &a, const Player &b) {
    return a.getFIDEID() < b.getFIDEID();
}

// Function to sort table
void sortTable() {
    int choice;
    cout << "\nChoose the field to sort by:\n";
    cout << "1. Name\n";
    cout << "2. Surname\n";
    cout << "3. Nationality\n";
    cout << "4. Ranking\n";
    cout << "5. Rating\n";
    cout << "6. Birth Year\n";
    cout << "7. FIDE ID\n";
    cout << "Please make a choice: ";

    if (!getValidateNumber(choice)) return;

    // Function pointer to compare two Player objects. Initially set to nullptr
    bool (*compare)(const Player &a, const Player &b) = nullptr;

    // accoring to the user choice, assign the comparison function to the compare pointer.
    switch (choice) {
        case 1: compare = compareByName; break;
        case 2: compare = compareBySurname; break;
        case 3: compare = compareByNationality; break;
        case 4: compare = compareByRanking; break;
        case 5: compare = compareByRating; break;
        case 6: compare = compareByBirthYear; break;
        case 7: compare = compareByFIDEID; break;
        default: return;
    }

    // Sorts the 'players' array in ascending order based on the custom comparison function 'compare'
    // which defines the sorting criteria for Player objects
    sort(players, players + countEntry, compare);
    cout << "**Table sorted successfully**\n";
}

void displayRow(int index) { // displays information of chosen player
    cout << "\n--Information of Player " << index + 1 << "--\n";
    cout << "Name: " << players[index].getName() << "\n";
    cout << "Surname: " << players[index].getSurname() << "\n";
    cout << "Nationality: " << players[index].getNationality() << "\n";
    cout << "Ranking: " << players[index].getRanking() << "\n";
    cout << "Rating: " << players[index].getRating() << "\n";
    cout << "Birth Year: " << players[index].getBirthYear() << "\n";
    cout << "FIDE ID: " << players[index].getFIDEID() << "\n";
}

void displayTable() {
    cout << left;
    
    // Print top border
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;

    // Print header row
    cout << "║ " << setw(3) << "No" 
         << " │ " << setw(15) << "Name"
         << " │ " << setw(15) << "Surname"
         << " │ " << setw(15) << "Nationality"
         << " │ " << setw(8) << "Ranking"
         << " │ " << setw(8) << "Rating"
         << " │ " << setw(15) << "Birth Year"
         << " │ " << setw(8) << "FIDE ID" 
         << " ║" << endl;
    
    // Print middle border
    cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════╣" << endl;

    // Print player data rows
    for (int i = 0; i < countEntry; i++) {
        cout << "║ " << setw(3) << (i + 1) 
             << " │ " << setw(15) << players[i].getName()
             << " │ " << setw(15) << players[i].getSurname()
             << " │ " << setw(15) << players[i].getNationality()
             << " │ " << setw(8) << players[i].getRanking()
             << " │ " << setw(8) << players[i].getRating()
             << " │ " << setw(15) << players[i].getBirthYear()
             << " │ " << setw(8) << players[i].getFIDEID() 
             << " ║" << endl;
    }

    // Print bottom border
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
}

bool handleUserSelection(int choice) {
    int playerID;
    int index;

    while (true) {
        
        cout << endl;
        cout << "╔════════════════════════════════════════╗" << endl;
        cout << "║       **** TOP CHESS PLAYERS ****      ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ 1. Load from file                      ║" << endl;
        cout << "║ 2. New Information Entry               ║" << endl;
        cout << "║ 3. Find Information                    ║" << endl;
        cout << "║ 4. List Information                    ║" << endl;
        cout << "║ 5. Sort                                ║" << endl;
        cout << "║ 6. Save to file                        ║" << endl;
        cout << "║ 7. Exit                                ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "Please make a choice (1-7): ";

        if (!getValidateNumber(choice)) 
            continue; // if input is invalid retry
        
        switch (choice) {
            case 1:
                loadFromFile();
                break;
            case 3: // find player the player by using fide id on the list
                cout << "\nEnter Player FIDE ID: ";
                if (getValidateNumber(playerID)) {
                    index = findRow(playerID);
                    if (index != -1) {
                        displayRow(index);
                        int subChoice;

                        while(true) {
                            cout << "\n1. Edit Information\n";
                            cout << "2. Delete Information\n";
                            cout << "3. Exit\n";
                            cout << "Please make a choice (1-3): ";

                             if (getValidateNumber(subChoice)) {
                                if (subChoice == 1) {
                                    players[index].editSingleRow();
                                } else if (subChoice == 2) {
                                    players[index].deleteRow();
                                    break;
                                }else if(subChoice == 3){
                                    break;
                                }else{
                                    cout<<"\nInvalid input. Please make a valid choice!";
                                }
                            }
                        }
                        
                    } else {
                        cout << "Player not found!\n";
                    }  
                }
                break;
            case 2: // instert new row
                insertNewRow();
                break;
            case 4: // display table
                displayTable();
                break;
            case 5: //sort table
                sortTable();
                break;
            case 6: // save to file
                saveToFile();
                break;
            case 7: //exit 
                cout << "Exiting...\n";
                return false;
            default:
                cout << "Invalid choice. Please try again!\n";
        }
    }

      
}

// Checks if the string is valid
bool getValidateString(string &input) { 
    getline(cin, input);

    if (input.empty()) { // cheks for empty input 
        cout << "Input cannot be empty. Please try again!\n";
        return false;
    }
    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];
        if (!isalpha(c) && c != ' ') { // checks for non-letter and non-space characters
            cout << "Invalid input. Please enter a valid string (letters only)!\n";
            return false;
        }
    }
    return true;
}

// Checks if the number is valid
bool getValidateNumber(int &number) { 
    string input;
    cin >> input;

    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];
        if (!isdigit(c)) { //if input include any non-integer character
            cout << "Invalid input. Please enter a valid number!\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
    }
    try {
        number = stoi(input); //converts string to integer
        return true;
    } catch (const exception&) {
        cout << "Invalid input. Please enter a valid number!\n";
        return false;
    }
}

//clears console
void clearConsole() { 
    try {
        #ifdef _WIN32 
            system("cls");  // to clear console for windows
        #else
            cout << "\033[H\033[2J";  //clear terminal for others (Mac, Linux etc.)
            cout.flush();
        #endif
    }
    catch (const exception& error) {
        cerr << "Error while clearing console: " << error.what() << endl;
    }
}
