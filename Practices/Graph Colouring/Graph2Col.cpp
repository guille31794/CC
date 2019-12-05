/*
    Software developed by
    Guillermo Girón García
    for practice 3
*/

#include "Headers.hpp"

int main(int argc, char const *argv[])
{
    loadList();
    createAdjMatrix();
    //TwoColRed(); 

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

void TwoColRed()
{
    ofstream dimacs{"reduction2.cnf", ofstream::out};
    string str{"c 2 colouring graph reduction\n"};
    
    dimacs << str; //.write(str.c_str(), str.length());

    str = "p cnf 30 85\n";

    dimacs << str;

    for(int i = 0; i != graphNodes; ++i)
    {
        generateClauses2(i, dimacs);
    }

    dimacs.close();
}

void generateClauses2(int node, ofstream& dimacs)
{
    //Own Clauses of a node
    int clauseBegin{node*2};
    string str{to_string(clauseBegin+1) 
    + " " + to_string(clauseBegin+2) + " 0\n"};
    dimacs << str;

    str = to_string(-(clauseBegin+1)) + " 0\n";
    dimacs << str;

    str = to_string(-(clauseBegin+2)) + " 0\n";
    dimacs << str;

    // Adjacency Clauses
    for(int i = node + 1; i < graphNodes; ++i)
    {
        if(adjMatrix[node][i])
        {
            int clauseBeginAdj{i*2};
            
        }
    }
}