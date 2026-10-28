/* rgp:protos */
#define RGP_SELF_DebugMenuWidgetHasPosFlagMaybe_209e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 DebugMenuWidgetHasPosFlagMaybe_209e20(s32 p0)
{
    s32 r;

    r = ((unsigned short)DebugMenuWidgetGetFlags_209de0(p0));
    return ((r & 4) != 0);
}
