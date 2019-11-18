/*
    Software developed by
    Guillermo Girón García
    for practice 3
*/

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// List that store all graphs conections
vector<list<unsigned>> adjL(10, list<unsigned>(3));
// Enum to represent colours
enum colour {R, G, B};

// Procedure that load list from file to memory
void loadList();

int main(int argc, char const *argv[])
{
    loadList();
    return 0;
}

void loadList()
{   
    ifstream list{"list.txt", ifstream::in};
    unsigned i{0};

    do
    {
        string str;
        getline(list, str);
        cout << atoi(str.c_str()) << endl;
        for_each(str.begin(), str.end(), 
        [i](char c)
        {
            adjL[i].push_back((unsigned)c);
        });
        //cout << adjL[i].front() << endl;
        ++i;
    }while(!list.eof());
    
    list.close();
}