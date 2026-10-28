/* rgp:protos */
#define RGP_SELF_SaveMenuMsgTableParse_376b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004831E0;

s32 SaveMenuMsgTableParse_376b40(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = ((s32)MsgTableParseText_28aab0(p0, p1, p2));
    D_004831E0 = r0;
    return r0;
}
