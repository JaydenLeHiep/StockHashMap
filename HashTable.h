//
// Created by Hiep Le on 04.03.23.
//

#ifndef ABGABE1_HASHTABLE_H
#define ABGABE1_HASHTABLE_H
#include "aktie.h"
#include <string>



static const int TABLE_SIZE = 11;

class HashTable {
private:
    // not sure ...
    // the way to create an array hash map

    // Each element of the table array is a pointer to an Aktie object.
    // This means that the array can hold up to TABLE_SIZE Aktie objects, but initially they are all set to nullptr
    Aktie *table[TABLE_SIZE];
public:

    HashTable() ;

    ~HashTable() ;

    // function for (maybe two table) name and kurz
    int hash(string name);

    //print element in hash
    void printTable() ;

//    // get position in another table
//    Aktie getPosition(int i);
    // add function for name and kurz
    void add(string name, string WKN) ;


    // two search function
    void search(string name);



    // two function to delete
    void deleteFunc(string name);

    //import file csv into Hashmap
    void import(string name, string filename);



    // save file into txt file and it needs name because every share has their own file
    void save(string name, string fileName);
    //load function
    void load(string fileName);
    // plot function
    void plot(string name);
};



#endif //ABGABE1_HASHTABLE_H
