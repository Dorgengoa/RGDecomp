/* rgp:protos */
#define RGP_SELF_FieldViewModeSet_2f3590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s32 D_0047EFD0.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_0047EFD0;

void FieldViewModeSet_2f3590(s32 value)
{
    D_0047EFD0 = value;
}
