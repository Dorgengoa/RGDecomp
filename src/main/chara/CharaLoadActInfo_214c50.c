#include "types.h"

extern s32 CharaActInfoInit_215600(void *, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x428];
    s32 m428;
};

s32 CharaLoadActInfo_214c50(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    s32 rv2;
    s32 r0;
    s32 rv1;

    t0 = p0->m428;
    rv2 = rv1;
    if (t0 != 0) {
        rv2 = 0;
    } else {
        r0 = CharaActInfoInit_215600((struct Obj0 *)((u8 *)p0 + 0x580), p1, p2, p3);
        rv1 = 1;
        if (r0 == 0) {
            rv1 = 0;
        } else {
            p0->m428 = p2;
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
