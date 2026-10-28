/* rgp:protos */
#define RGP_SELF_SetTaskListChanged_1f56b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data u8 D_004819B0.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_004819B0;

void SetTaskListChanged_1f56b0(u8 value)
{
    D_004819B0 = value;
}
