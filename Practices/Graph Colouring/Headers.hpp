/*
    Software developed by
    Guillermo Girón García
    for practice 3
*/

#ifndef adjList_hpp
#define adjList_hpp
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

unsigned graphNodes{10}, colours3{3}, colours2{2};

// List that store all graphs conections
vector<list<unsigned>> adjL(graphNodes, list<unsigned>{});

// adjacency matrix
bool adjMatrix[10][10];

// Procedure that load list from file to memory
void loadList();

// Procedure to create an adjacency 
void createAdjMatrix();

// Procedure that computes the reduction
void ThreeColRed();
void TwoColRed();

// Prodedure that generates clauses for any node
// Clauses going to be: node number + 1 * [1..3]
// Example: node 0 -> 1 2 3, represents node 0
// can be red, blue or green.
// For node 1 -> 4 5 6 and so on.
void generateClauses2(int, ofstream&);
void generateClauses3(int, ofstream&);

#endif