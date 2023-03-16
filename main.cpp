#include "HashTable.h"
#include <string>

using namespace std;




int main() {
    cout << "Welcome!!! This is your Finance Bro " << endl;
    string answer;
    cout << "Do you want help from our Finance Bro (yes/no): " << endl;
    cin >> answer;
    HashTable table1;
    HashTable table2;
    while (answer == "yes") {
        //table 1 for name , table 2 for kurz

        string answerInGame;
        string input;
        string name;
        string kurz;
        string WKN;
        string nameFile;

        while(input != "no"){
            cout << "What do you want to do?" << endl;
            cout << "You can add, delete, import, save, search, load, plot or seeTable." <<endl;
            // a is add, d is delete, i is import, s is search, sa is save, l is load
            cin >> input;
            if (input == "add") {
                // Let the user know they have to give name and kurzel

                cout << "Give name" << endl;
                cin >> name;
                cout << "Give kurz" << endl;
                cin >> kurz;
                cout << "Give WKN" << endl;
                cin >> WKN;
                table1.add(name, WKN);
                table2.add(kurz, WKN);


            } else if (input == "delete") {
                // this function too
                // this function has to deal with
                cout << "Give name" << endl;
                cin >> name;
                cout << "Give kurz" << endl;
                cin >> kurz;
                table1.deleteFunc(name);
                table2.deleteFunc(kurz);


            } else if (input == "import") {

                cout << "Give name" << endl;
                cin >> name;
                cout << "Give file name" << endl;
                cin >> nameFile;
                table1.import(name, nameFile);
                table2.import(name, nameFile);

            } else if (input == "save") {
                // tell user, he/she should only give name or kurz

                cout << "NAME OR KURZ" << endl;
                cin >> answerInGame;
                if (answerInGame == "name") {
                    cout << "Give name" << endl;
                    cin >> name;
                    cout << "Give file name" << endl;
                    cin >> nameFile;
                    table1.save(name, nameFile);
                } else if (answerInGame == "kurz") {
                    cout << "Give kurz" << endl;
                    cin >> kurz;
                    cout << "Give file name" << endl;
                    cin >> nameFile;
                    table2.save(kurz, nameFile);
                }


            } else if (input == "search") {
                // tell use, he/she should only give name or kurz

                cout << "NAME OR KURZ" << endl;
                cin >> answerInGame;
                if (answerInGame == "name") {
                    cout << "Give name" << endl;
                    cin >> name;

                    table1.search(name);
                } else if (answerInGame == "kurz") {
                    cout << "Give kurz" << endl;
                    cin >> kurz;
                    table2.search(kurz);
                }
            }else if (input == "load") {
                cout << "Give file name" << endl;
                cin >> nameFile;
                table1.load(nameFile);
            }else if (input == "seeTable") {
                cout << "Table of Names" << endl;
                table1.printTable();
                cout << "Table of short names" << endl;
                table2.printTable();
            }else if(input == "plot"){
                cout << "Name pls" << endl;
                cin >> name;
                table1.plot(name);
            }
            if (answer == "no") {

                cout << "Stop the program" << endl;
                break;
            }
        }

    }
    return 0;
}