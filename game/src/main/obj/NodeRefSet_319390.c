/* rgp:protos */
#define RGP_SELF_NodeRefSet_319390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0x2];
    u8 m08;
};

void NodeRefSet_319390(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m00 = p1;
    p0->m02 = p2;
    p0->m04 = p4;
    p0->m08 = 0;
    if (p3 != 0) {
        strcpy((struct Obj0 *)((u8 *)p0 + 8), p3);
    }
}
