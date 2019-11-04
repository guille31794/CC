/*
    Practice 2
    Software developed by:
    Guillermo Girón García
*/

#include <iostream>
#include <vector>

using namespace std;

unsigned dim{5};
//Costs matrix declaration
vector<vector<unsigned>> cm{dim,{dim}};

//Random costs matrix generator
void cmGenerator(vector<vector<unsigned>>&);

// Compute the next k-combinations
void nextKComb();

// Show next k-combinations throw std::out
void showComb();

int main(int argc, char const *argv[])
{
    
    return 0;
}

void cmGenerator(vector<vector<unsigned>>& v)
{
    for(auto i : v)
        for(auto j : i)
            j = rand()%100+1;

    for(auto i = 0; i < dim; ++i)
        v[i][i] = 0;
}