#include "types.h"

extern void GetGridCellPos_28ed30(s32, void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

void GetGridCellPosOffset_28ecd0(s32 p0, struct Obj0 *p1, struct Obj1 *p2, s32 p3, s32 p4)
{
    s32 t0;
    s32 t1;

    GetGridCellPos_28ed30(p0, p1, p2);
    t0 = p1->m00;
    p1->m00 = (t0 + p3);
    t1 = p2->m00;
    p2->m00 = (t1 + p4);
}
