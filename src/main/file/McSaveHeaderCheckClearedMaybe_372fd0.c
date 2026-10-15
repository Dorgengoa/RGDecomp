#include "types.h"

extern s32 AnyOfFourIdsNegative_3eec60(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483168;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x334];
    s16 m33A;
};

void McSaveHeaderCheckClearedMaybe_372fd0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s16 t0;
    s16 t1;

    if (p0 != 0) {
        r0 = AnyOfFourIdsNegative_3eec60(p0);
        if (r0 != 0) {
            return;
        }
        t0 = p0->m04;
        if (t0 >= 0x21) {
            t1 = p0->m33A;
            if (t1 >= 3) {
                *(u8 *)((u8 *)&D_00483168 + p1) = 1;
            }
        }
        return;
    }
}
