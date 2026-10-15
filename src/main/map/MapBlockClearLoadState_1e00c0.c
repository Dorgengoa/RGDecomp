#include "types.h"

extern void MapDataClearLoadState_1e7c30(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC0];
    s32 mC0;
    s32 mC4;
    s16 mC8;
    s16 mCA;
};

void MapBlockClearLoadState_1e00c0(struct Obj0 *p0)
{
    MapDataClearLoadState_1e7c30(p0);
    p0->mC0 = 0;
    p0->mC8 = 0;
    p0->mC4 = 0;
    p0->mCA = 0;
}
