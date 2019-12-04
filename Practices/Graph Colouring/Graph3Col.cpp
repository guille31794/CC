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
    ThreeColRed(); 

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
    ofstream dimacs{"reduction3.cnf", ofstream::out};
    string str{"c 3 colouring graph reduction\n"};
    
    dimacs << str; //.write(str.c_str(), str.length());

    str = "p cnf 30 85\n";

    dimacs << str;

    for(int i = 0; i != graphNodes; ++i)
    {
        generateClauses3(i, dimacs);
    }

    dimacs.close();
}

void generateClauses3(int node, ofstream& dimacs)
{
    // Own clauses of a node
    int clauseBegin{node*3};
    string str{to_string(clauseBegin+1)};
    
    for(int i = clauseBegin + 2; i <= clauseBegin+colours3; 
    ++i)
        str.append(" " + to_string(i));
    
    str.append(" 0\n");
    dimacs << str;

    for(int i = clauseBegin+1; i <= clauseBegin + colours3; 
    ++i)
    {
        for(int j = i+1; j <= clauseBegin+colours3; ++j)
        {
            str = to_string(-i);
            str.append(" " + to_string(-j) + " 0\n");
            dimacs << str;
        }
    }

    // Adjacency clauses
    for(int i = node + 1; i < graphNodes; ++i)
    {
        if(adjMatrix[node][i])
        {
            int clauseBeginAdj{i*3};
            for(int j = 1; j <= colours; ++j)
            {
                str = to_string(-(clauseBegin+j)) + " " + 
                to_string(-(clauseBeginAdj+j)) + " 0\n";
                dimacs << str;
            }
        }
    }
}