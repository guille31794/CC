#include <iostream>
#include "ram.h"

void program();

// Driver to execute a RAM program computing a binary function.

memory r(128), m(1024);

int main()
{
  using namespace std;

  // Data input through the standard input.

  integer a = 0, b = 0;
  cout << "a = ";
  cin >> a;
  cout << "b = ";
  cin >> b;

  // RAM data input (memory initialization).

  m[1] = a;
  m[2] = b;

  // Program execution.

  program();

  // RAM data output (memory reading).

  integer c = m[0];

  // Data output through the standard output. 

  cout << "f(a, b) = " << c << endl;  
}
