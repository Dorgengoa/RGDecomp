#include "types.h"

extern void CharaDataSubRecRelease_1ee6d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x66];
    s16 m66;
    s32 m68;
    s16 m6C;
};

void CharaDataRecReleaseSubRecsByKey_1ee050(struct Obj0 *p0, s32 p1)
{
    s32 l0;
    s32 t0;
    s16 t1;

    l0 = 0;
    while (l0 < p0->m66) {
        t0 = p0->m68;
        t1 = *(s16 *)((u8 *)t0 + (((l0 * 0xC) + l0) << 3) + 0x8);
        if (p1 == t1) {
            CharaDataSubRecRelease_1ee6d0((t0 + (((l0 * 0xC) + l0) << 3)));
        }
        l0 = (l0 + 1);
    }
    p0->m6C = 0;
}
