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

unsigned graphNodes{10};

// List that store all graphs conections
vector<list<unsigned>> adjL(graphNodes, list<unsigned>{});

// Enum to represent colours
enum colour {R, G, B};

// adjacency matrix
bool adjMatrix[10][10];

// Procedure that load list from file to memory
void loadList();

// Procedure to create an adjacency 
void createAdjMatrix();

// Procedure that computes the reduction
void ThreeColRed();

// Prodedure that generates clauses for any node
void generateClauses();

#endif