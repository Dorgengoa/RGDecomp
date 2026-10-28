/* rgp:protos */
#define RGP_SELF_MenuSetPanelHandles_35b8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x134];
    s32 m134;
    s32 m138;
    s32 m13C;
    s32 m140;
};

void MenuSetPanelHandles_35b8c0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m134 = p1;
    p0->m138 = p2;
    p0->m13C = p3;
    p0->m140 = p4;
}
