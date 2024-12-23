#include <iostream>
#include <list>
#include <string>

using namespace std;


void PrintList(list<string> l) {
    for (auto p : l) {
        cout << p << endl;
    }
    return;
}


int main() {
    // Нужно будет добавить перед самой длинной фамилией
    string surnameToAdd = "fam";
    list<string> surnames;

    // Заполним разными фамилиями
    surnames.push_back("fimoZOV");
    surnames.push_back("HUYhUYlanov");
    surnames.push_back("Hitling");
    surnames.push_back("Hotler");
    surnames.push_back("Zalupa");
    surnames.push_back("ZOVZOVranov");


    string longSurname = surnames.front();

    auto idx = surnames.begin();

    for (auto i = surnames.begin(); i != surnames.end(); i++) {
        if (longSurname.length() < (*i).length()) {
            longSurname = (*i);
            idx = i;
        }
    }
    
    surnames.insert(idx, surnameToAdd);

    PrintList(surnames);

    return 0;
}