/*
    Software developed by
    Guillermo Girón García
    for practice 3
*/

#include "adjList.hpp"

int main(int argc, char const *argv[])
{
    loadList();
    createAdjMatrix();
    //ThreeColRed(); 

    cout << endl;
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
        
        for_each(str.begin(), str.end(), 
        [i](char c)
        {
            if(!isspace(c))
                adjL[i].push_back((unsigned)(c - '0'));
        });
        
        ++i;
    }while(!list.eof());
    
    list.close();
}

void createAdjMatrix()
{
    for(int i = 0; i < adjL.size(); ++i)
        for(int j = 0; j < adjL.size(); ++j)
            adjMatrix[i][j] = 0;

    for(int i = 0; i < adjL.size(); ++i)
        for(auto it : adjL[i])
            adjMatrix[i][it] = 1;
        
}

void ThreeColRed()
{
    ofstream dimacs{"reduction.cfg", ofstream::out};
    string str{"c 3 colouring graph reduction"};
    
    dimacs.write(str.c_str(), str.length());

    str = "p cnf 30 120";

    dimacs.write(str.c_str(), str.size());

    for(int i = 1; i != graphNodes; ++i)
    {
        
    }

    dimacs.close();
}

void generateClauses()
{

}