#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>

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