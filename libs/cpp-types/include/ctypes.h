#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <string>
#include <stdexcept>
#include <optional>
#include <cstdint>
#include <vector>
#include <variant>
#include <any>
#include <cstring>

/** \remark: 1's complement
 *
 */

/** \remark: 2's complement
 *     \subpage: unsigned inteager
 *               [0 0 0 0] → 0,
 *               [1 1 1 1] → 15
 *     \subpage: signed inteager (MSB → for sign)
 *               [0 0 0 0] → 0,
 *               [0 1 1 1] → 7,
 *               [1 0 0 0] → -8,
 *               [1 1 1 1] → -1
 *     \subpage: float
 *               15000 →       (+){1.5}  x 10^[4]
 *               -380000 →     (-){3.8}  x 10^[5]
 *               0.0000123 →   (+){1.23} x 10^[-5]
 *               -0.0000123 →  (-){1.23} x 10^[-5]
 *        - stucture: ( ) + { } + [ ] : Refer to IEEE 754 → [Sign] x [Mantissa] x 2^[Exponent]
 *        - Sign 1bit + Exponent 8bit + Mantissa 23bit (Total 32bit float variable)
 *        - Example) INF: (1) + {11111111} + [0000...000],
 *                   NAN:     + {11111111} + [Not a zero],
 *                   DENOM:   + {00000000} + [Not a zero]
 *        - Googling IEEE 754 converter :)
 */

void types_example();

class catType
{
public:
  void print()
  {
    std::cout << "meow~ " << n << std::endl;
  }

private:
  int n{10};
};

struct sType1 // 4 + (4, padding) + 8 = 16
{
  int i;    // 4 bytes
  double d; // 8 bytes
};

/** \note: shared memory  */
union uType1 // 8 bytes
{
  int i;    // 4 bytes
  double d; // 8 bytes
};

// Union-like class / tagged union
union uType2 // 32 bytes
{
  std::string str;      // 32 bytes
  std::vector<int> vec; // 24 bytes
  ~uType2() {}          // needs to know which member is active, only possible in union-like class
};

struct sType2
{
  int i;
  double d;
  float f;
};

union uType3
{
  int i;
  double d;
  float f;
};