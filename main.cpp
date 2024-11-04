#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(const list<Goat> trip);
int main_menu();

void count_goats_by_age(const list<Goat>& trip, int age);
void find_oldest_goat(const list<goat>& trip);
void find_youngest_goat(const list<goat>& trip);
void sort_goats_by_age(const list<goat>& trip);
void sort_goats_by_name(const list<goat>& trip);
void remove_goats_by_color(const list<goat>& trip, const string& color);
void display_unique_colors(const list<goat>& trip);
void suffle_goat_list(const list<goat>& trip);

int main() {
    srand(time(0));
    

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
    while (sel != 4) {
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
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void count_goats_by_age(list<Goat> &trip, int age) {
    int count = count_if(trip.begin(), trip.end(), [age](const Goat& g) { return g.get_age() > age; });
    cout << "Goats older than " << age << ": " << count << endl;
}

void find_oldest_goat(list<Goat> &trip) {
    auto oldest = max_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
    if (oldest != trip.end())
        cout << "Oldest goat: " << oldest->get_name() << " (" << oldest->get_age() << " years)" << endl;
}

void find_youngest_goat(list<Goat> &trip) {
    auto youngest = min_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
    if (youngest != trip.end())
        cout << "Youngest goat: " << youngest->get_name() << " (" << youngest->get_age() << " years)" << endl;
}

void sort_goats_by_age(list<Goat> &trip) {
    trip.sort( [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
    cout << "Goats sorted by age." << endl;
}

void sort_goats_by_name(list<Goat> &trip) {
    trip.sort( [](const Goat& a, const Goat& b) { return a.get_name() < b.get_name(); });
    cout << "Goats sorted by name." << endl;
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
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}
