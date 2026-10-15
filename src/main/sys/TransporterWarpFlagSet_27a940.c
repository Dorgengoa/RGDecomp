#include "types.h"
/* retail STORES the zero and RE-READS the byte: the global is volatile, or
   mwcc would keep the 0 in a register and never touch memory twice. */
extern volatile u8 D_00482178;
void TransporterWarpFlagSet_27a940(void)
{
    D_00482178 = 0;
    D_00482178 |= 5;
}
