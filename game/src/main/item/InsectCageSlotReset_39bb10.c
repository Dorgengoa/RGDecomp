/* rgp:protos */
#define RGP_SELF_InsectCageSlotReset_39bb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0xC];
    s32 m14;
    s32 m18;
    s16 m1C;
    s16 m1E;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
};

void InsectCageSlotReset_39bb10(struct Obj0 *p0)
{
    p0->m04 = 0;
    p0->m00 = 0;
    LoadHandleReset_1ccc10((struct Obj0 *)((u8 *)p0 + 8));
    p0->m1C = -1;
    p0->m18 = 0;
    p0->m14 = 0;
    p0->m1E = 0;
    p0->m20 = -1;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
}
