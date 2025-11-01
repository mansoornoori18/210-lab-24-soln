#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void find_goat(list<Goat>trip);
void reverse_trip(list<Goat>&trip);
void double_goat_ages(list<Goat> &trip);
void find_oldest_goat(list<Goat> &trip); // prototype for oldest goat

int main_menu();

int main() {
    srand(time(0));
    bool again;

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

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 8) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
            cout << "searching for a goat.\n";
            find_goat(trip);
            break;
            case 5:
            cout << " reversing\n";
            reverse_trip(trip);
            break;
            
            case 6:
            cout << "double the ages of goats\n";
            double_goat_ages(trip);
            break;
            case 7:
            cout << "findding the oldest goat\n";
            find_oldest_goat(trip);
            break;
                  
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find a goat by name\n";
    cout << "[5] Reverse goat list\n"; 
    cout << "[6] Double all goats ages\n";
    cout << "[7] To find the oldest Goat\n";
    cout << "[8] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 8) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

// function for find_goat
void find_goat(list<Goat>trip){
    cout << "search for a goat by naem" << endl;
    string searchName;
    cout << "Enter the name of the goat:";
    cin >> searchName;

    auto it = find_if(trip.begin(), trip.end(), [&](const Goat&g){
        return g.get_name() ==searchName;
    });
    if (it != trip.end()) {
        cout << "goat found: "
        << it->get_name() << "(" << it->get_age() << ", " << it->get_color() << "),\n";
    }else {
        cout << "Gaot Not found. \n";
    }

}
// function to reverse the goat list 
void reverse_trip(list<Goat> &trip){
    cout << "reversing the goat list.. \n";
    trip.reverse();
    display_trip(trip);
}
void double_goat_ages(list<Goat> &trip){
    cout << "double the age of all the goats\n";
    for (auto &g : trip){
        g.set_age(g.get_age()*2);
    }
    cout << "all goats ages have been doubled\n";
    display_trip(trip);
}
// function to find the oldest goat
void find_oldest_goat(list<Goat> &trip){
    if (trip.empty()){
        cout << "no goats in the trip\n";
        return;
    }
    auto oldest = trip.begin();
    for (auto it = trip.begin(); it != trip.end(); ++it){
        if (it->get_age() > oldest->get_age()){
            oldest = it;
        }
    }
    cout << "the oldest goat is: " << oldest->get_name() << " (" << oldest->get_age() 
    << ", " << oldest->get_color() << " )\n";

}


