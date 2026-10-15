#include "types.h"

extern s32 CharaSysStatusFindFree_3a16b0(void *);
extern void StatusEntryApply_3a6000(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xB94];
    struct Obj1 *mB94;
};

struct Obj1 {
    u8 m00;
};

s32 CharaSysStatusAdd_3a1630(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    struct Obj1 * t0;
    u8 t1;
    s32 rv2;
    struct Obj1 * t2;

    r0 = CharaSysStatusFindFree_3a16b0(p0);
    if (r0 == 0) {
        return 0;
    }
    t0 = p0->mB94;
    t1 = p0->mB94->m00;
    StatusEntryApply_3a6000(r0, t1, p1, 0);
    if (t1 == 0xFF) {
        rv2 = 1;
    } else {
        rv2 = t1 + 1;
    }
    t2 = p0->mB94;
    p0->mB94->m00 = rv2;
    return r0;
}
