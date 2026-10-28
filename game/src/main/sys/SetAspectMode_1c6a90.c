/* rgp:protos */
#define RGP_SELF_SetAspectMode_1c6a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s32 D_00481638.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_00481638;

void SetAspectMode_1c6a90(s32 value)
{
    D_00481638 = value;
}
