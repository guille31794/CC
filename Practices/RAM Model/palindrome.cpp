#include "ram.h"

void palindrome()
{
        //To reach 1º string position
        inc(0);
        inc(0);
        //To reach length position
        inc(1);
        //Length
        load(2,1);
        load(6,1);
        inc(2);
        dec(6);
        //1º String element
        load(3,0);
        //Last string element
        load(4, 2);
        cgoto(3, one);
        //R5 Value always 0
        cgoto(5,zero);
    zero:
        cgoto(4, fail);
        cgoto(5, next);
    one:
        cgoto(4,next);
        cgoto(5, fail);
    next:
        dec(6);
        dec(6);
        cgoto(6,conti);
        cgoto(5, accept);
    conti:
        //Continue execution
        dec(2);
        inc(0);
        load(4,2);
        load(3,0);
        cgoto(3, one);
        cgoto(5, zero);
    accept:
        inc(5);
        store(5,7);
        cgoto(5,exit);
    fail:
        store(5, 7);
    exit:
        dec(5);
}

//Driver program

#include <iostream>
#include <iomanip>

memory r, m(1024);
unsigned counter{0};

int main(int argc, char const *argv[])
{
    using namespace std;

    //Data input through the standard input
    string s;
    cout << "Input string? >> ";
    cin >> s;

    //RAM initialization
    initialize(8); //Seven registers

    //RAM data input (memory initialization).
    m[1] = s.size();
    for(string::size_type i = 0; i != s.size(); ++i)
    {   
        //every zero will be converted to -1
        if(s[i] == '0')
            m[i+2] = -1;
        else
            m[i+2] = 1;
    }

    //Program execution
    palindrome();

    //RAM data output (memory reading).

    integer l = m[0];

    //Data output
    if(m[0])
        cout << "Input string is a palindrome " << counter << 
        " steps taken" << endl;
    else
        cout << "Input string is not a palindrome " << counter << 
        " steps taken" << endl;

    return 0;
}
