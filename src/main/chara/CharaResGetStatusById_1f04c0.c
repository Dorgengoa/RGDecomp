#include "types.h"

extern void * CharaResFindById_1f0530(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x64];
    s16 m64;
};

s16 CharaResGetStatusById_1f04c0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s16 t0;

    r0 = CharaResFindById_1f0530(p0, p1);
    if (r0 == 0) {
        return (s16)-1;
    }
    t0 = r0->m64;
    return t0;
}
