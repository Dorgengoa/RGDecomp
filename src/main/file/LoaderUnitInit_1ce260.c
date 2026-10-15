#include "types.h"

extern void LoaderUnitReset_1ce370(void *);
extern void PathLocalize_1c28c0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x80];
    s16 m80;
    u8 pad082[0x2];
    s16 m84;
    s16 m86;
    s32 m88;
    s32 m8C;
};

void LoaderUnitInit_1ce260(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    LoaderUnitReset_1ce370(p0);
    p0->m80 = p1;
    PathLocalize_1c28c0(p0, p2);
    p0->m84 = p5;
    if (p3 != 0) {
        if (p4 != 0) {
            p0->m86 = 1;
            p0->m88 = p3;
            p0->m8C = p4;
        } else {
            p0->m86 = 0;
        }
    } else {
        p0->m86 = 0;
    }
}
