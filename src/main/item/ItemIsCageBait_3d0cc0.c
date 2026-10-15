#include "types.h"

extern s32 ItemIsInsectFood_3d45b0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    struct Obj1 *m10;
};

struct Obj1 {
    u8 pad000[0x2];
    s8 m02;
};

s32 ItemIsCageBait_3d0cc0(s32 p0, struct Obj0 *p1)
{
    s32 rv2;
    s32 r0;
    s32 rv1;
    struct Obj1 * t0;
    s8 t1;

    rv2 = rv1;
    if (p1 == 0) {
        rv2 = 0;
    } else {
        r0 = ItemIsInsectFood_3d45b0(p1);
        rv1 = ((t1 ^ 0xD) != 0);
        if (r0 == 0) {
            rv1 = 0;
        } else {
            t0 = p1->m10;
            t1 = p1->m10->m02;
            rv1 = ((t1 ^ 0xD) != 0);
        }
        rv2 = rv1;
    }
    return rv2;
}
