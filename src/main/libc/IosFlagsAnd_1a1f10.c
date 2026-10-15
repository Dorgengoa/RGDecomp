#include "types.h"
/* three `andi 0xFFFF`: both operands and the result are register-resident u16. */
u16 IosFlagsAnd_1a1f10(u16 a, u16 b) { return a & b; }
