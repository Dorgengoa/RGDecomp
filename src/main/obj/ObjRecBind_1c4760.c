#include "types.h"

extern s32 strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x20];
    s32 m24;
};

s32 ObjRecBind_1c4760(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 t0;

    if (p2 == 0 || p1 == 0) {
        return -1;
    }
    p0->m00 = 0;
    p0->m24 = p1;
    r0 = strcpy((struct Obj0 *)((u8 *)p0 + 8), p2);
    t0 = p0->m00;
    p0->m00 = (t0 | 4);
    return 0;
}
