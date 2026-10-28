/* rgp:protos */
#define RGP_SELF_MenuWinSetUvRect_26c300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x6C];
    s32 m6C;
    s32 m70;
    s32 m74;
    s32 m78;
};

void MenuWinSetUvRect_26c300(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m6C = p1;
    p0->m70 = p2;
    p0->m74 = p3;
    p0->m78 = p4;
}
