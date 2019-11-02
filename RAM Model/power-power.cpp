// Input:
//
//   m[1]: a
//   m[2]: b
//
// Output:
//
//   m[0]: c
//
// Precondition:
//
//   b ≥ 0
//
// Postcondition:
//
//   c = a ^ (2 ^ b)

#include "ram.h"

void program()
{
  reset(0);
  inc(0);
  load(1, 0);
  inc(0);
  load(2, 0);
  reset(0);
 loop:
  dec(2);
  cgoto(2, next);
  cgoto(0, end);
 next:
  mul(1, 1);
  cgoto(2, loop);
 end:
  store(1, 0);
}
