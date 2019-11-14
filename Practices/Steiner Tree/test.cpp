#include<iostream>
#include<vector>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<vector<int>> v{5,{5}};

    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
        {
            v[i][j] = j;
            cout << v[i,j] << " " << endl;
        }
    return 0;
}
