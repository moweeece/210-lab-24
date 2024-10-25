// COMSC-210 | Mauricio Espinosa | Lab 24
// IDE Used: Visual Studio Code & Github

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>    // change to set for this lab
#include <ctime> // for seeding time
#include <cstdlib> // for randoms
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again = true;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    set<Goat> trip;

    while (again) {

        int choice = main_menu();

        switch (choice)
        {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                again = false;
                break;
            default:
                break;
        }

    }

    return 0;
}


// function to display main menu, returns user's selection
int main_menu() {
    int userChoice;

    do {
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << "[1] Add a goat" << endl;
        cout << "[2] Delete a goat" << endl;
        cout << "[3] List goats" << endl;
        cout << "[4] Quit" << endl;
        cout << "Choice --> ";
        cin >> userChoice;

        if (userChoice < 1 || userChoice > 4) {
            cout << "Invalid input" << endl;
        }

    } while (userChoice < 1 || userChoice > 4);
    
    return userChoice;
}


// function to add a goat to the trip
void add_goat(set<Goat> &trip, string names[], string colors[])
{
    int nameIndex = rand() % SZ_NAMES;
    int randAge = rand() % MAX_AGE;
    int colorIndex = rand() % SZ_COLORS;

    Goat newGoat(names[nameIndex], randAge, colors[colorIndex]);
    trip.insert(newGoat);

    cout << "Goat added!" << endl << endl;
}


// function to delete a goat from the trip
void delete_goat(set<Goat> &trip)
{
    int userDelete;
    userDelete = select_goat(trip);

    // using an iterator to move to chosen position then delete the goat
    auto it = trip.begin();   // set iterator to beginning of list
    advance(it, userDelete);  // advance iterator to user selection point
    trip.erase(it);           // delete goat

    cout << "Goat deleted!" << endl << endl;

}


// function to display the current trip
void display_trip(set<Goat> trip)
{
    if (trip.empty())
    {
        cout << "No goats to display!" << endl << endl;
    }

    if (!trip.empty())
    {
        // range based for loop to go through the entire list and display contents
        for (const auto& goat : trip)
        {
            int i = 1;
            cout << left << setw(5) << "";
            cout << "[" << i << "] " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")" << endl;
            i++;
        }
    }
    
    cout << endl;
}


// function to select a goat
int select_goat(set<Goat> trip)
{
    display_trip(trip);
    int userSelection;

    do {
        cout << "Select a goat --> ";
        cin >> userSelection;

        // user entry input validation
        if (userSelection < 0 || userSelection > trip.size())
        {
            cout << "Invalid entry" << endl;
        }

    } while (userSelection < 0 || userSelection > trip.size());
    

    return userSelection - 1;  // -1 for proper indexing in the list
}