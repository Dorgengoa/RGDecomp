#include "types.h"

/* Zero the small-data u8 D_004821BC. */

extern u8 D_004821BC;

void ClearPad2Enabled_2882a0(void)
{
    D_004821BC = 0;
}
