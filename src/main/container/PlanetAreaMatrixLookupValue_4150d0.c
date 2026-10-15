#include "types.h"

extern void * PlanetAreaMatrixLookup_415100(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 PlanetAreaMatrixLookupValue_4150d0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = PlanetAreaMatrixLookup_415100(p0, p1, p2, p3, p4);
    if (r0 != 0) {
        t0 = r0->m04;
        return t0;
    }
    return 0;
}
