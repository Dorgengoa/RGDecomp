/* rgp:protos */
#define RGP_SELF_EventCastSetWinColor_257dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventCastSetWinColor_257dc0(s32 p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 rv2;
    s32 t1;
    s32 rv1;
    s32 r0;

    if (p1 < 0 || p1 >= 0x20) {
        return 0;
    }
    t0 = *(s32 *)((u8 *)p0 + (p1 << 4));
    if (t0 != 2) {
        rv2 = 0;
    } else {
        t1 = *(s32 *)((u8 *)p0 + (p1 << 4) + 0xC);
        rv1 = 1;
        if (t1 == 0) {
            rv1 = 0;
        } else {
            r0 = MenuWinSetColor_26c380(t1, p2);
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
