/*
    Practice 2
    Software developed by:
    Guillermo Girón García
    Compiled under:
    g++ (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008
    using -std=c++17 -O2 flags
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <list>

using namespace std;

unsigned dim{25};

class Binario 
{     
    //Class to represent a binary number, to use for all node choice combinations.
    public:
        int NOnes;      //Amount of ones in the number.
        
        Binario(unsigned siz): NOnes(0), Bins(siz, 0){}
        
        void inc()      //Increment the binary number by one. Produces an error with overflows.
        {
            if(NOnes <= dim)
            {
                vector<unsigned>::iterator it = Bins.begin();
                while(*it == 1 && it != Bins.end())
                {
                    *it = 0;
                    it++;
                    NOnes--;
                }
                *it = 1;
                NOnes++;
            }
        }

        unsigned size() const{return Bins.size();}   //Return size of number

        int operator[](int indice){return Bins[indice];}
    private:
        vector<unsigned> Bins;   //Vector of ones and zeros.

};

//Costs matrix declaration
vector<vector<unsigned>> cm(dim, vector<unsigned>(dim));

//Random costs matrix generator
void cmGenerator(vector<vector<unsigned>>&);

// Compute the next k-combinations
vector<vector<unsigned>> nextKComb(vector<vector<unsigned>>&);

// Show next k-combinations throw std::out
void showComb(const vector<vector<unsigned>>&);

// Implementation of Prim's algorithm
vector<pair<unsigned, unsigned>> Prim(vector<vector<unsigned>>&, 
unsigned);

// Sub-algorithm needed for Prim's
unsigned select(vector<unsigned>&, vector<unsigned>&); 

// Sub-algorithm needed for Prim's
void update(vector<unsigned>&, vector<unsigned>&,
vector<unsigned>&, unsigned, vector<vector<unsigned>>&);

// Compute the distance needed for a determined combination of nodes
unsigned distance(vector<pair<unsigned, unsigned>>&);

// Creates submatrix joining costs from cm & combinations of nodes
vector<vector<unsigned>> subMComb
(vector<vector<unsigned>>&, Binario&);

// Creates combinations, and compute it distances
void generateTree();

// Auxiliar functions for printing and debugging
void showPairs(vector<pair<unsigned, unsigned>>&);
void printCM(vector<vector<unsigned>>&);

int main(int argc, char const *argv[])
{
    cmGenerator(cm);
    //printCM(cm);

    generateTree();

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

vector<vector<unsigned>> nextKComb(vector<vector<unsigned>>& v)
{
    vector<vector<unsigned>> comb(1, vector<unsigned>(v.size()));
    
    for(int i = 0; i < v[0].size(); ++i)
        comb[0][i] = i;

    do
    {
        while (next_permutation(comb[0].begin(), comb[0].end()))
            comb.push_back(comb[0]);
    
        comb[0].pop_back();
    } while (comb[0].size() > 5);
    
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
Prim(vector<vector<unsigned>>& p, unsigned n)
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
        // Minimum distance node
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

void update(vector<unsigned>& c, 
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

void showPairs(vector<pair<unsigned, unsigned>>& S)
{
    for (auto &&i : S)
        cout << i.first << " " << i.second << '\n';
    
    cout << endl;
}

void printCM(vector<vector<unsigned>>& cm)
{
    for (auto &&i : cm)
    {   
        cout << "| ";
        for (auto &&it : i)
            cout << it << " ";
        
        cout << "|\n";
    }

    cout << endl;
}

unsigned distance(vector<pair<unsigned, unsigned>>& S)
{
    unsigned d{0};
    for (auto &&i : S)
        d += i.second;
    
    return d;
}

vector<vector<unsigned>> subMComb
(vector<vector<unsigned>>& cm, Binario& comb)
{
    unsigned size{(unsigned)(5+comb.NOnes)};
    vector<vector<unsigned>> subM(size, {size});
    vector<unsigned> position;

    for(int i = 0; i < comb.size(); ++i)
        if(comb[i])
            position.push_back(i);

    vector<unsigned>::iterator it = position.begin();

    for (int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            subM[i][j] = cm[i][j];

    for(int i = 0; i < size; ++i)
    {
        it = position.begin();

        for(int j = 5; j < size; ++j)
        {
            subM[i][j] = cm[i][*it];
            ++it;
        }
    }

    for(int i = 5; i < size; ++i)
    {
        it = position.begin();
        
        for(int j = 0; j < size; ++j)
        {
            subM[i][j] = cm[i][*it];
            ++it;
        }
    }
        
    return subM;
}

void generateTree()
{
    // Nodes to check plus the compulsory ones (n)
    unsigned n{20}, 
    //Minimum distance for cover all graph nodes
    d{numeric_limits<unsigned>::max()};
    //Used to generate combinations
    Binario comb{n};

    while(comb.NOnes < 25)
    {
        vector<vector<unsigned>> subM{subMComb(cm, comb)};
        //showComb(comb);
        vector<pair<unsigned, unsigned>> S{Prim(subM, dim)};
        //showPairs(S);
        d = min(distance(S), d);
        comb.inc();
    }
    
    cout << "Minimun distance is: " << d << endl;
}