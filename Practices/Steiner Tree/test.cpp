#include<iostream>
#include<vector>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<vector<int>> v{5,{5}};

    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            v[i][j] = j;
            cout << v[i][j] << " ";
        }
        cout << '\n';
    }

    unsigned size{(unsigned)v.size()};
    v.resize(v.size()+3);
    for(auto &&i : v)
        i.resize(size+3);

    for(int i = 0; i <= size; ++i)
        v[i][size] = size;

    for(int i = 0; i < size; ++i)
        v[size][i] = size;

    for(int i = 0; i < v.size(); ++i)
    {
        for(int j = 0; j < v.size(); ++j)
        {
            v[i][j] = j;
            cout << v[i][j] << " ";
        }
        cout << '\n';
    }

    cout << endl;
        
    return 0;
}
