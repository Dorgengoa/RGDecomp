#include "types.h"

extern void HandleEntriesReleaseExcept_3f0b90(s32, s32);
extern s32 HandleEntriesReleaseExcept_3f0aa0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0x20];
    u8 m2C;
};

s32 HandleEntriesReleaseAll_3ec300(struct Obj0 *p0)
{
    u8 t0;
    s32 rv2;
    s32 t1;
    s32 t2;
    s32 r1;

    t0 = p0->m2C;
    rv2 = 1;
    if ((t0 & 1) != 0) {
        rv2 = 0;
    } else {
        t1 = p0->m08;
        HandleEntriesReleaseExcept_3f0b90(t1, -1);
        t2 = p0->m08;
        r1 = HandleEntriesReleaseExcept_3f0aa0(t2, -1);
        rv2 = 1;
    }
    return rv2;
}
