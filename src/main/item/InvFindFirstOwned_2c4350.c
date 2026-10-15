#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 InvFindFirstOwned_2c4350(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 l1;
    s32 t0;
    s32 t1;
    s32 r2;
    s32 t2;

    r0 = GetGameData_1fede0();
    if (p1 <= 0) {
        return -1;
    }
    l1 = 0;
    while (l1 < p1) {
        t0 = r0->m18;
        t1 = *(s32 *)((u8 *)p0 + (l1 << 2));
        r2 = InvFindInCategoryRange_3c8370(t0, t1, 0, -1, 0, 0);
        if (r2 != 0) {
            t2 = *(s32 *)((u8 *)p0 + (l1 << 2));
            return t2;
        }
        l1 = (l1 + 1);
    }
    return -1;
}
