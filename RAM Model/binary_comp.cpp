#include "ram.h"

void binary_com()
{
        //load length1 to r(1)
        inc(0);
        load(1,0);
        load(5,0);
        //load length2 to r(4)
        inc(1);
        inc(1);
        load(3,1);
        //start
    decr:
        dec(5);
        dec(3);
        cgoto(5, cmplen);
        cgoto(3, fail);
        cgoto(6, accept);
    loop:
        inc(0);
        load(2,0);
        inc(1);
        load(4,1);
        cgoto(2, cmpone);
    cmpzero:
        cgoto(4, fail);
        cgoto(6, decr);
    cmpone:
        cgoto(4, decr);
        cgoto(6, fail);
    cmplen:
        cgoto(3, loop);
        cgoto(6, fail);
    accept:
        inc(6);
        store(6,7);
        cgoto(6, end);
    fail:
        store(6,7);
    end:
        dec(6);
}

#include <iostream>
memory r, m(1024);
unsigned counter{0};

int main(int argc, char const *argv[])
{
    using namespace std;

    //Data input through the standard input
    string b1{}, b2{};
    cout << "Insert first binary number >> ";
    cin >> b1;
    cout << "Insert second binary number >> ";
    cin >> b2;
    
    size_t l1{b1.size()},
    l2{b2.size()};

    //RAM initialization
    initialize(8);

    //RAM data input (memory initialization).
    size_t j;
    m[1] = b1.size();
    for(string::size_type i = 0; i != b1.size(); ++i)
    {
        if(b1[i] == '0')
            m[i+2] = -1;
        else
            m[i+2] = 1;
        j = i + 3;
    }

    m[j] = b2.size();
    ++j;
    for(string::size_type i = 0; i != b2.size() ; ++i ,++j)
    {
        if(b2[i] == '0')
            m[j] = -1;
        else
            m[j] = 1;
    }

    //Program execution
    binary_com();

    //RAM data output (memory reading).

    integer l = m[0];

    //Data output
    if(m[0])
        cout << "The numbers are equal " << counter << 
        " steps taken" << endl;
    else
        cout << "The numbers are different" << counter << 
        " steps taken" << endl;

    return 0;
}
