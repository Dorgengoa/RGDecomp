#include "types.h"

extern void MapAreaSlotLoad_1e2fd0(void *, s32, void *, void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045B490[];

struct Obj0;
struct Obj1;

struct Obj0 {
    s16 m00;
};

struct Obj1 {
    u8 pad000[0x6];
    s16 m06;
};

void MapMgrLoadAreaSlot2_1e30f0(struct Obj1 *p0, struct Obj0 *p1, s32 p2, s32 p3)
{
    s16 t0;

    t0 = p1->m00;
    p0->m06 = t0;
    MapAreaSlotLoad_1e2fd0(p0, 2, p1, D_0045B490, p2, p3);
}
