#include "types.h"

extern s32 StrEqualNonNull_1ca6c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044B7D0[];

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

s32 CharaCmdFindByName_228ac0(s32 p0)
{
    struct Obj0 *l0;
    s32 r1;
    s32 t0;

    if (p0 == 0) {
        return 0;
    }
    l0 = (struct Obj0 *)D_0044B7D0;
    while (l0->m00 != 0) {
        r1 = StrEqualNonNull_1ca6c0(l0->m00, p0);
        if (r1 != 0) {
            t0 = l0->m04;
            return t0;
        }
        l0 = (struct Obj0 *)((u8 *)l0 + 8);
    }
    return 0;
}
