/* rgp:protos */
#define RGP_SELF_MenuWinSetBlink_26c1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC4];
    s32 mC4;
    s32 mC8;
    s32 mCC;
};

void MenuWinSetBlink_26c1a0(struct Obj0 *p0, s32 p1, s32 p2)
{
    p0->mC4 = p1;
    if (p1 != 0) {
        p0->mC8 = p2;
        p0->mCC = 0;
    }
}
