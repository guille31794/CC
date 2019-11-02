#include "ram.h"

// Sample RAM program (with symbolic labels).

// Compute the length of a zero-terminated string.
//
// Input:  m[1], m[2], ...	(the string)
// Output: m[0]			(the length)

void program()
{
  reset(0);
  reset(1);			// i = 0;
 loop:				// do {
  inc(1);			//   ++i;
  load(2, 1);			//   c = m[i];
  dec(2);			//   --c;
  cgoto(2, next);
  cgoto(0, end);
 next:
  cgoto(2, loop);		// } while (c >= 0);
 end:
  dec(1);                       // --i;
  store(1, 0);                  // m[0] = i;
}

// Driver program.

#include <iostream>
#include <iomanip>

memory r, m(1024);

int main()
{
  using namespace std;

  // Data input through the standard input.

  string s = "";
  cout << "Input string? ";
  getline(cin, s);

  // RAM initialization.

  initialize(3);		// Three registers.

  // RAM data input (memory initialization).

  for (string::size_type i = 0; i != s.size(); ++i)
    m[i + 1] = static_cast<unsigned char>(s[i]);
  m[s.size() + 1] = 0;

  // Program execution.

  program();

  // RAM data output (memory reading).

  integer l = m[0];

  // Data output through the standard output. 

  cout << "Representation: ";
  for (string::size_type i = 1; i != s.size() + 2; ++i)
    cout << setw(3) << setfill('0') << m[i] << ' ';
  cout << "\nLength " << l << '.' << endl;  
}
