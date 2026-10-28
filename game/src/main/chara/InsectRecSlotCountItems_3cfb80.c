/* rgp:protos */
#define RGP_SELF_InsectRecSlotCountItems_3cfb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004838E8;

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 InsectRecSlotCountItems_3cfb80(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 l0;
    s32 l1;
    s32 l2;
    s32 t2;
    s32 rv3;

    t0 = D_004838E8;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m18;
    l0 = 0;
    l2 = 0;
    do {
        t2 = *(s32 *)((u8 *)t1 + (l2 << 2) + 0xC);
        rv3 = l0;
        if (t2 != 0) {
            rv3 = (l0 + 1);
        }
        l0 = rv3;
        l1 = ((l2 + 1) < 5);
        l2 = (l2 + 1);
    } while (l1 != 0);
    return l0;
}
