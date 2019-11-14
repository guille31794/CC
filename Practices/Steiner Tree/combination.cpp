/*
    Practice 2
    Software developed by:
    Guillermo Girón García
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

unsigned dim{5};
//Costs matrix declaration
vector<vector<unsigned>> cm(dim, vector<unsigned>(5));

//Random costs matrix generator
void cmGenerator(vector<vector<unsigned>>&);

// Compute the next k-combinations
vector<vector<unsigned>> nextKComb(vector<vector<unsigned>>&, int);

// Show next k-combinations throw std::out
void showComb(const vector<vector<unsigned>>&);

// Implementation of Prim's algorithm
vector<pair<unsigned, unsigned>> Prim(vector<vector<unsigned>>&, int compulsory);

// Sub-algorithm needed for Prim's
unsigned select(vector<unsigned>&, vector<unsigned>&); 

// Sub-algorithm needed for Prim's
pair<vector<unsigned>, vector<unsigned>> update(vector<unsigned>&, vector<unsigned>&,
vector<unsigned>&, unsigned, vector<vector<unsigned>>&);

int main(int argc, char const *argv[])
{
    cmGenerator(cm);
    
    vector<vector<unsigned>> v{nextKComb(cm, 5)};

    showComb(v);

    vector<pair<unsigned, unsigned>> S
    {Prim(cm, 5)};

    return 0;
}

void cmGenerator(vector<vector<unsigned>>& v)
{
    for(int i = 0; i < dim; ++i)
        for(int j = 0; j < dim; ++j)
            v[i][j] = rand()%100+1;

    for(auto i = 0; i < dim; ++i)
        v[i][i] = 0;
}

vector<vector<unsigned>> nextKComb(vector<vector<unsigned>>& v, int k)
{
    vector<vector<unsigned>> comb(1, vector<unsigned>(v.size()));
    
    for(int i = 0; i < v[0].size(); ++i)
        comb[0][i] = i;

    int i = 1;
    
    while (next_permutation(comb[0].begin(), comb[0].end()) && i != k)
    {
        comb.push_back(comb[0]);
        ++i;
    }
    
    return comb;    
}

void showComb(const vector<vector<unsigned>>& v)
{
    for(auto i : v)
    {
        cout << "| ";
        for(auto it : i)
            cout << it << " ";
        
        cout << " |\n";
    }

    cout << endl;
}

vector<pair<unsigned, unsigned>> 
Prim(vector<vector<unsigned>>& p, int n)
{
    //Set of predecessor and it's distances
    vector<pair<unsigned, unsigned>> S;
    //Set of vertex
    vector<unsigned> C(n-1);
    //Node predecessor
    vector<unsigned> c(n);
    //Distances from actual node to the neighbors
    vector<unsigned> d(n);

    c[0] = 0;
    d[0] = 0;

    for(int j = 1; j < n; ++j)
    {
        C.push_back(j);
        c[j] = 1;
        d[j] = p[0][j];
    }

    while(!C.empty())
    {
        unsigned k = select(C,d);
        C.erase(find(C.begin(), C.end(), k));
        S.push_back(make_pair(c[k], k));
        update(c, d, C, k, p);
    }

    return S;
}

unsigned select(vector<unsigned>& C, vector<unsigned>& d)
{
    unsigned k{},
    v{numeric_limits<unsigned>::max()};

    /*for(auto it : C)
        if(d[it] < v)
        {
            v = d[it];
            k = it;
        }*/

    for_each(C.begin(), C.end(), 
    [d, &v, &k](unsigned n)
    {
        if(d[n] < v)
        {
            v = d[n]; 
            k = n;
        }
    });

    return k;
}

pair<vector<unsigned>, vector<unsigned>> update(vector<unsigned>& c, 
vector<unsigned>& d, vector<unsigned>& C, unsigned k, 
vector<vector<unsigned>>& p)
{
    for_each(C.begin(), C.end(),
    [&c, &d, k, &p](unsigned j)
    {
        if(p[j][k] < d[j])
        {
            c[j] = k;
            d[j] = p[k][j];
        }
    });
}