#include "types.h"

extern void strncpy(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x1];
    u8 m01;
    u8 pad002[0xE];
    u8 m10;
};

void InsectItemSetName_3d1f60(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    struct Obj1 * t1;
    struct Obj1 * t2;

    if (p1 == 0) {
        t0 = p0->m18;
        p0->m18->m01 = 0;
    } else {
        t1 = p0->m18;
        strncpy((struct Obj1 *)((u8 *)t1 + 1), p1, 0x10);
        t2 = p0->m18;
        p0->m18->m10 = 0;
    }
}
