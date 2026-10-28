/* rgp:protos */
#define RGP_SELF_ObjRecFlagsSnapshotStackInit_1d7650 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 m00;
};

void ObjRecFlagsSnapshotStackInit_1d7650(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;
    s32 l2;
    s32 l3;

    l1 = 0;
    do {
        l2 = (((l1 << 3) - l1) << 2);
        l3 = 0;
        do {
            *(u8 *)((u8 *)(p0 + (((l1 << 3) - l1) << 2)) + l3 + 0x1) = 0;
            l2 = ((l3 + 1) < 0x1C);
            l3 = (l3 + 1);
        } while (l2 != 0);
        l0 = ((l1 + 1) < 8);
        l1 = (l1 + 1);
    } while (l0 != 0);
    p0->m00 = 0;
}
