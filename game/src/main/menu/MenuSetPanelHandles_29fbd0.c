/* rgp:protos */
#define RGP_SELF_MenuSetPanelHandles_29fbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C4];
    s32 m4C4;
    s32 m4C8;
    s32 m4CC;
    s32 m4D0;
};

s32 MenuSetPanelHandles_29fbd0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m4CC = p3;
    p0->m4C4 = p1;
    p0->m4C8 = p2;
    p0->m4D0 = p4;
    return 1;
}
