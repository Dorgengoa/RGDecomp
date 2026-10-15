#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x58];
    f32 m58;
    f32 m5C;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s32 m00;
};

void UiPanelGetOffset_33d530(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2)
{
    f32 t0;
    f32 t1;

    t0 = p0->m58;
    p1->m00 = ((s32)t0);
    t1 = p0->m5C;
    p2->m00 = ((s32)t1);
}
