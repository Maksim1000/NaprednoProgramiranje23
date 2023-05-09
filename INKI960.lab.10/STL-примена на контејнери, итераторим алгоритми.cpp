#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxDigit(int num) {
    int maxDigit = 0;
    while (num > 0) {
        int digit = num % 10;
        if (digit > maxDigit) {
            maxDigit = digit;
        }
        num /= 10;
    }
    return maxDigit;
}

int main() {
    const string BrojNalndeks = "960";
    const string Izveduvac = "Maksim";
    string tekst = "Phill Collins A Groovy Kind of Love\nWhen i'm feeling groove\n all i have to do\n is take a look at you";

    tekst.erase(remove_if(tekst.begin(), tekst.end(), [](char c) { return !isalnum(c); }), tekst.end());

    int broj;
    cout << "Vnesi trocifren broj: ";
    cin >> broj;
    int maxDigit = getMaxDigit(broj);
    cout << "Najgolemiot znamen e: " << maxDigit << endl;

    vector<int> asciiValues;
    for (char c : tekst) {
        asciiValues.push_back(int(c) * maxDigit);
    }

    sort(asciiValues.begin(), asciiValues.end());
    cout << "Sortiran vektor: ";
    for (int val : asciiValues) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}