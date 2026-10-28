/* rgp:protos */
#define RGP_SELF_SetPendingFadeFrames_27bd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s32 D_00482170.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_00482170;

void SetPendingFadeFrames_27bd50(s32 value)
{
    D_00482170 = value;
}
