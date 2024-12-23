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


bool Compare(string surname1, string surname2) {
    return surname1.length() < surname2.length();
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

    surnames.sort(Compare);

    PrintList(surnames);

    return 0;
}