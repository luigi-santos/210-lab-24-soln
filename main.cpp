#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <random>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(const list<Goat> trip);
int main_menu();

void count_goats_by_age(const list<Goat>& trip, int age);
void find_oldest_goat(const list<Goat>& trip);
void find_youngest_goat(const list<Goat>& trip);
void sort_goats_by_age(const list<Goat>& trip);
void sort_goats_by_name(const list<Goat>& trip);
void remove_goats_by_color(const list<Goat>& trip, const string& color);
void display_unique_colors(const list<Goat>& trip);
void suffle_goat_list(const list<Goat>& trip);

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
    while (sel != 12) {
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
            case 4: {
                int age;
                cout << "Enter age: ";
                cin >> age;
                count_goats_by_age(trip, age);
                break;
            }
            case 5:
                find_oldest_goat(trip);
                break;
            case 6:
                find_youngest_goat(trip);
                break;
            case 7:
                sort_goats_by_age(trip);
                break;
            case 8:
                sort_goats_by_name(trip);
                break;
            case 9:{
                string color;
                cout << "Enter color to remove: ";
                cin >> color;
                remove_goats_by_color(trip, color);
                break;
            }
            case 10:
                display_unique_colors(trip);
                break;
            case 11:
                shuffle_goat_list(trip);
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
    cout << "[1]Add a goat [2]Delete a goat [3]List goats" << endl;
    cout << "[4]Count goats by age [5]Find oldest goat [6]Find youngest goat" << endl;
    cout << "[7]Sort goats by age [8]Sort goats by name [9]Remove goats by color" << endl;
    cout << "[10]Display unique colors [11]Shuffle goats [12}Quit" << endl;
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
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
    trip.sort([](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
    cout << "Goats sorted by age." << endl;
}

void sort_goats_by_name(list<Goat> &trip) {
    trip.sort([](const Goat& a, const Goat& b) { return a.get_name() < b.get_name(); });
    cout << "Goats sorted by name." << endl;
}

void remove_goats_by_color(list<Goat> &trip, const string& color) {
    trip.remove_if([&color](const Goat& g) { return g.get_color() == color; });
    cout << "Removed goats with color" << color << "." << endl;
}

void display_unique_colors(list<Goat> &trip) {
    set<string> colors;
    transform(trip.begin(), trip.end(), inserter(colors, colors.end()), [](const Goat& g) { return g.get_color(); });
    cout << "Unique colors: ";
    for (const auto& color : colors) {
        cout << color << " ";
    }
    cout << endl;
}

void shuffle_goat_list(list<Goat>& trip) {
    vector<Goat> goatVector(trip.begin(), trip.end());
    random_device rd;
    mt19937 g(rd());
    shuffle(goatVector.begin(), goatVector.end(), g);
    trip.assign(goatVector.begin(), goatVector.end());
    cout << "Shuffled goat list" << endl;
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
