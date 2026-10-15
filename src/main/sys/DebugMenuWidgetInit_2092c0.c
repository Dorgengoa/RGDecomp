#include "types.h"

extern void strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C620[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
    s16 m1C;
    s16 m1E;
    s16 m20;
    s16 m22;
    s16 m24;
    s16 m26;
    s16 m28;
    s16 m2A;
};

void DebugMenuWidgetInit_2092c0(struct Obj0 *p0)
{
    strcpy(p0, D_0045C620);
    p0->m22 = 0;
    p0->m24 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m26 = 0;
    p0->m28 = 0;
    p0->m1E = 0;
    p0->m20 = 0;
    p0->m2A = 0;
}
