#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <string>

using namespace std;

struct student {
    string ime;
    string prezime;
    string indeks;
};

char tocniPrvi[4] = { 'b', 'a', 'c', 'b' };
char tocniVtori[4] = { 'b', 'a', 'b', 'a' };
char tocniTreti[4][2] = { {'c', 'd'}, {'a', 'e'}, {'c', 'd'}, {'b', 'e'} };

// Funkcija koja se koristi za primanje na vlez

void studentInput(student& lice) {
    cout << "Vnesete go imeto na studentot: ";
    cin >> lice.ime;
    cout << "Vnesete go prezimeto na studentot: ";
    cin >> lice.prezime;

    do {
        cout << "Vnesete go indeksot na studentot: ";
        cin >> lice.indeks;
    } while (lice.indeks.size() != 3);
}
// Funkcija koja se koristi za zapishuvanje na odgovorot vo datoteka

void writeOdgovor(fstream& file, char odg, char odg2, int br) {
    if (br == 1) {
        file << "\nPisani odgovori:" << endl;
    }
    file << br << ". " << odg << " " << odg2 << endl;
}
// Funkcija koja se koristi za proverka na odgovorot i boduvanje

float checkOdgovor(int brojnaprasanje, char answer, char answer2) {


    if (brojnaprasanje <= 4) {

        if (answer == tocniPrvi[brojnaprasanje - 1])
            return 1.5;

    }
    else if (brojnaprasanje > 4 && brojnaprasanje <= 8) {
        if (answer == tocniVtori[brojnaprasanje - 5])
            return 3;
    }
    else if (brojnaprasanje > 8 && brojnaprasanje <= 12) {
        if (((answer == tocniTreti[brojnaprasanje - 9][0]) && (answer2 == tocniTreti[brojnaprasanje - 9][1])) || ((answer == tocniTreti[brojnaprasanje - 9][1]) && (answer2 == tocniTreti[brojnaprasanje - 9][0])))
            return 8;
    }
}
// Funkcija koja ovozmozuva proverka na vnes kaj odgovorot i ispishuvanje na odgovorot vo datoteka

float handleInput(int brojprasanje, fstream& file) {

    char odgovor{}, odgovor2{};
    if (brojprasanje <= 4) {
        do {
            cout << "Vashiot odgovor: ";
            cin >> odgovor;
        } while (odgovor != 'a' && odgovor != 'b' && odgovor != 'c');
        writeOdgovor(file, odgovor, ' ', brojprasanje);

    }
    else if (brojprasanje > 4 && brojprasanje <= 8) {
        do {
            cout << "Vashiot odgovor: ";
            cin >> odgovor;
        } while (odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd');
        writeOdgovor(file, odgovor, ' ', brojprasanje);
    }
    else if (brojprasanje > 8 && brojprasanje <= 12) {
        do {
            cout << "Vashiot odgovor: ";
            cin >> odgovor;
        } while (odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd' && odgovor != 'e');
        do {
            cout << "Vashiot odgovor: ";
            cin >> odgovor2;
        } while ((odgovor2 == odgovor) || (odgovor2 != 'a' && odgovor2 != 'b' && odgovor2 != 'c' && odgovor2 != 'd' && odgovor2 != 'e'));
        writeOdgovor(file, odgovor, odgovor2, brojprasanje);
    }

    return checkOdgovor(brojprasanje, odgovor, odgovor2);
}

// Funkcija koja se koristi za proverka na poeni i vrakanje na vrednosta na ocenkata

int score(float poeni) {
    if (poeni >= 0 && poeni <= 24)
        return 5;
    else if (poeni >= 25 && poeni <= 32)
        return 6;
    else if (poeni >= 32.5 && poeni <= 37)
        return 7;
    else if (poeni >= 37.5 && poeni <= 40.5)
        return 8;
    else if (poeni >= 41 && poeni <= 45)
        return 9;
    else if (poeni >= 45.5 && poeni <= 50)
        return 10;
}

// Funkcija za pechatenje na tabela so tochnite odgovori

void answersTable() {
    cout << "Tocni odgovori na prasanjata se:" << endl;
    for (int i = 1; i <= 12; i++) {
        if (i <= 4)
            cout << i << ". " << tocniPrvi[i - 1] << endl;
        else if (i > 4 && i <= 8)
            cout << i << ". " << tocniVtori[i - 5] << endl;
        else if (i > 8 && i <= 12)
            cout << i << ". " << tocniTreti[i - 9][0] << " " << tocniTreti[i - 9][1] << endl;
    }
}

int main() {

    fstream file, test;
    student lice;
    string prasanje;
    int brojnaprasanje = 1;
    float poeni = 0;
    studentInput(lice);

    // Kreiranje na datotekata so ime i prezime na studentot

    const string filename = lice.ime + lice.prezime + "INKI" + lice.indeks;
    ifstream fileExist(filename);

    if (fileExist.good()) {
        //File exists
        cout << "\nVekje ste go resavale testot! " << endl;
        exit(0);
    }
    else {
        //File does not exist
        file.open(filename.c_str(), ios::out);
        file.close();

        // Students.log

        string filenames = "Students.log.txt";
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", timeinfo);

        ofstream files(filenames, ios_base::app);

        if (!files.good()) {
            files.open(filenames);
        }

        ifstream filess(filenames, ios_base::app);

        int count = 0;
        string line;
        while (getline(filess, line)) {
            count++;
        }

        files << count + 1 << ". " << buffer << "; " << lice.ime << "; " << lice.prezime << "; " << "INKI" << lice.indeks << "\n";

        files.close();
        file.open(filename, ios::app);
        // Otvoranje na datotekata so prasanja i prevzemanje na soodvetnoto prasanje i negovite odgovori
        file << "Ime: " << lice.ime << endl;
        file << "Prezime: " << lice.prezime << endl;
        file << "Indeks: " << "INKI" << lice.indeks << endl;
        file << "Vreme na start: " << buffer << endl;
        file.close();
        test.open("prasanja.txt", ios::in);
        while (getline(test, prasanje)) {
            for (int i = 0; i < prasanje.size(); i++) {
                if (prasanje[i] == ';') {
                    cout << endl;
                    i++;
                }
                else
                    cout << prasanje[i];
            }
            cout << endl;
            if (brojnaprasanje == 13)
                break;

            file.open(filename.c_str(), ios::app);
            poeni += handleInput(brojnaprasanje, file);
            file.close();
            brojnaprasanje++;
        }

        time_t nowend = time(0);
        timeinfo = localtime(&nowend);
        strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", timeinfo);

        test.close();
        file.open(filename, ios::app);
        int ocenka = score(poeni);
        cout << "Vashata ocenka: " << ocenka << endl;

        file << "\nPoeni: " << poeni << endl;
        file << "Ocenka: " << ocenka << endl;
        file << "Vreme na kraj: " << buffer << endl;
        file.close();
        answersTable();

        return 0;
    }
}
