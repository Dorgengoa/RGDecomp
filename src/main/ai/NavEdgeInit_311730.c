#include "types.h"

extern void NavEdgeReset_3117a0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s32 m04;
    u8 pad008[0x4];
    s16 m0C;
};

void NavEdgeInit_311730(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    NavEdgeReset_3117a0(p0);
    p0->m0C = p1;
    p0->m00 = p2;
    p0->m02 = p3;
    p0->m04 = p4;
}
