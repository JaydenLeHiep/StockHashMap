//
// Created by Hiep Le on 04.03.23.
//

#include "HashTable.h"
#include "aktie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    // Deallocate each Entry element
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }

}

int HashTable::hash(string name) {
    int hash = 0;
    for (int i = 0; i < name.length(); i++) {
        hash = hash * 31 + int(name[i]);
        // the reason for using 31, because 31 is an odd prime number that is not too close to a power of 2, which helps to ensure good distribution properties
        // the main reason because I saw it in the folie 🥸🥸
    }
    return hash % TABLE_SIZE;
}

void HashTable::printTable() {
    cout << "THE HASH TABLE" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != nullptr) {
            cout << i << " " <<table[i] << endl;
        }
    }
}


void HashTable::add(string name, string WKN) {
    int index = hash(name);

    int step = 0;
    int i = index;
    while (table[i] != nullptr) {

        step++;
        i = (index + step * step) % TABLE_SIZE;
        // quadratic probing step to find the place
    }
    if (table[i] == nullptr) {
        table[i] = new Aktie{name, WKN};
        // every index in the array we create a new object (struct)

    }
}


void HashTable::search(string name) {
    int index = hash(name);
    int step = 0;
    int i = index;
    while (table[i] != nullptr && table[i]->name != name) {
        step++;
        i = (index + step * step) % TABLE_SIZE;
    }
    if (table[i] != nullptr && table[i]->name == name) {

        cout << table[i]->name << " " << table[i]->WKN << " and the Infor ..." << endl;
        cout << "DATE | OPEN | HIGH | LOW | CLOSE | ADJ_CLOSE" << endl;

        StockData *current = &(table[i]->StockData);
        current = current->next;// !!! Trick to fix the first row error 🥲🥲🥲
        while (current != nullptr) {
            cout << current->date << "| " << current->open << "| " << current->high << "| "
                 << current->low << "| " << current->close << "| " << current->adj_close << "| "
                 << current->volume << endl;
            current = current->next;
        }
    } else {
        cout << "We don't have that share in system" << endl;
    }
}


void HashTable::deleteFunc(string name) {
    int index = hash(name);
    int step = 0;
    int i = index;
    while (table[i] != nullptr && table[i]->name != name) {
        step++;
        i = (index + step * step) % TABLE_SIZE;
    }
    if (table[i] != nullptr && table[i]->name == name) {
        delete table[i];
        table[i] = nullptr;// to know this point is already deleted
    } else {
        cout << "We don't have that share to delete" << endl;
    }
}


// linked list to add new information from 1st day to the last day of the month
void printList(StockData *head) {
    StockData *current = head;
    while (current != NULL) {
        cout << "Date: " << current->date << endl;
        cout << "Open: " << current->open << endl;
        cout << "High: " << current->high << endl;
        cout << "Low: " << current->low << endl;
        cout << "Close: " << current->close << endl;
        cout << "Adj Close: " << current->adj_close << endl;
        cout << "Volume: " << current->volume << endl;
        cout << endl;
        current = current->next;
    }
}

StockData *
addFirst(string date, float open, float high, float low, float close, float adj_close, int volume, StockData *head) {

    StockData *newNode = new StockData;
    newNode->date = date;
    newNode->open = open;
    newNode->high = high;
    newNode->low = low;
    newNode->close = close;
    newNode->adj_close = adj_close;
    newNode->volume = volume;

    newNode->next = head;

    head = newNode;
    return head;
}

StockData *
addLast(string date, float open, float high, float low, float close, float adj_close, int volume, StockData *head) {
    if (head == nullptr) {
        return addFirst(date, open, high, low, close, adj_close, volume, head);
    }
    StockData *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    StockData *newNode = new StockData;
    newNode->date = date;
    newNode->open = open;
    newNode->high = high;
    newNode->low = low;
    newNode->close = close;
    newNode->adj_close = adj_close;
    newNode->volume = volume;
    temp->next = newNode;

    return head;

}

//



void HashTable::import(std::string name, std::string filename) {
    int index = hash(name);
    int step = 0;
    int i = index;
    while (table[i] != nullptr && table[i]->name != name) {
        step++;
        i = (index + step * step) % TABLE_SIZE;
    }
    if (table[i] != nullptr && table[i]->name == name) {

        std::ifstream inf(filename);
        string line;
        getline(inf, line); // skip the header line
        StockData *head = &table[i]->StockData;

        if (!inf.is_open()) {
            std::cerr << "Could not open file!" << std::endl;

        }
        while (getline(inf, line)) {
            stringstream ss(line);
            string date_str, open_str, high_str, low_str, close_str, adj_close_str, volume_str;
            getline(ss, date_str, ',');
            getline(ss, open_str, ',');
            getline(ss, high_str, ',');
            getline(ss, low_str, ',');
            getline(ss, close_str, ',');
            getline(ss, adj_close_str, ',');
            getline(ss, volume_str);

            head = addLast(date_str, stof(open_str), stof(high_str), stof(low_str), stof(close_str),
                           stof(adj_close_str), stoi(volume_str), head);
        }
        inf.close();
    }
}

//
//void HashTable::save(std::string name, std::string fileName) {
//    ofstream myfile(fileName);
//    if (myfile.is_open()) {
//        int index = hash(name);
//        int step = 0;
//        int i = index;
//        while (table[i] != nullptr && table[i]->name != name) {
//            step++;
//            i = (index + step * step) % TABLE_SIZE;
//        }
//        if (table[i] != nullptr && table[i]->name == name) {
//            myfile << "  DATE         | OPEN  | HIGH  | LOW   | CLOSE | ADJ_CLOSE | VOLUME    \n";
//            myfile << "  ------------|-------|-------|-------|-------|-----------|-----------\n";
//
//            StockData *current = &(table[i]->StockData);
//            current = current->next; // Trick to fix the first row error
//            while (current != nullptr) {
//                myfile << std::setw(12) << current->date << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->open << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->high << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->low << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->close << " | ";
//                myfile << std::setw(9) << std::fixed << std::setprecision(3) << current->adj_close << " | ";
//                myfile << std::setw(9) << current->volume << "\n";
//
//                current = current->next;
//            }
//        } else {
//            cout << "We don't have that share in system" << endl;
//        }
//        myfile.close();
//    } else {
//        cout << "Unable to open file";
//    }
//}
void HashTable::save(std::string name, std::string fileName) {
    ofstream myfile(fileName);
    if (myfile.is_open()) {
        int index = hash(name);
        int step = 0;
        int i = index;
        while (table[i] != nullptr && table[i]->name != name) {
            step++;
            i = (index + step * step) % TABLE_SIZE;
        }
        if (table[i] != nullptr && table[i]->name == name) {
            myfile << "  DATE         | OPEN  | HIGH  | LOW   | CLOSE | ADJ_CLOSE | VOLUME    \n";
            myfile << "  ------------|-------|-------|-------|-------|-----------|-----------\n";

            StockData *current = &(table[i]->StockData);
            current = current->next; // Trick to fix the first row error
            while (current != nullptr) {
//                myfile << std::setw(12) << current->date << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->open << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->high << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->low << " | ";
//                myfile << std::setw(5) << std::fixed << std::setprecision(2) << current->close << " | ";
//                myfile << std::setw(9) << std::fixed << std::setprecision(3) << current->adj_close << " | ";
//                myfile << std::setw(9) << current->volume << "\n";
                myfile << table[i]->name << table[i]->WKN << table[i]->kurz;

                current = current->next;
            }
        } else {
            cout << "We don't have that share in system" << endl;
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}




void HashTable::load(std::string fileName) {


    std::ifstream inf(fileName);
    string line;
    getline(inf, line); // skip the header line


    if (!inf.is_open()) {
        std::cerr << "Could not open file!" << std::endl;

    }
    while (getline(inf, line)) {
        cout << line << endl;
    }
    inf.close();

}

void HashTable::plot(std::string name) {
    int index = hash(name);
    int step = 0;
    int i = index;
    while (table[i] != nullptr && table[i]->name != name) {
        step++;
        i = (index + step * step) % TABLE_SIZE;
    }
    if (table[i] != nullptr && table[i]->name == name) {
        cout << "  DATE         | OPEN  | HIGH  | LOW   | CLOSE | ADJ_CLOSE | VOLUME    \n";
        cout << "  ------------|-------|-------|-------|-------|-----------|-----------\n";

        StockData *current = &(table[i]->StockData);
        current = current->next; // Trick to fix the first row error
        while (current != nullptr) {
            cout << std::setw(12) << current->date << " | ";
            cout << std::setw(5) << std::fixed << std::setprecision(2) << current->open << " | ";
            cout << std::setw(5) << std::fixed << std::setprecision(2) << current->high << " | ";
            cout << std::setw(5) << std::fixed << std::setprecision(2) << current->low << " | ";
            cout << std::setw(5) << std::fixed << std::setprecision(2) << current->close << " | ";
            cout << std::setw(9) << std::fixed << std::setprecision(3) << current->adj_close << " | ";
            cout << std::setw(9) << current->volume << "\n";

            current = current->next;
        }
    } else {
        cout << "We don't have that share in system" << endl;
    }
}

