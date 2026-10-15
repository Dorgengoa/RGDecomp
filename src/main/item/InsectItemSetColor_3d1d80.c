#include "types.h"

extern s32 InsectColorForSpeciesMaybe_3d2700(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_00465D88;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x10];
    struct Obj1 *m10;
    u8 pad014[0x4];
    struct Obj2 *m18;
};

struct Obj1 {
    u8 pad000[0x4];
    s16 m04;
};

struct Obj2 {
    u8 pad000[0x2C];
    s32 m2C;
};

s32 InsectItemSetColor_3d1d80(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s32 r0;
    struct Obj2 * t2;
    struct Obj2 * t3;
    s32 t4;
    struct Obj2 * t5;
    s32 t6;
    s32 t7;
    s32 rv1;
    struct Obj2 * t8;
    s32 t9;

    t0 = p0->m10;
    t1 = p0->m10->m04;
    r0 = InsectColorForSpeciesMaybe_3d2700(t1);
    t2 = p0->m18;
    p0->m18->m2C = r0;
    t3 = p0->m18;
    t4 = p0->m18->m2C;
    if (t4 < 0) {
        p0->m18->m2C = 0;
    }
    t5 = p0->m18;
    t7 = p0->m18->m2C;
    t6 = D_00465D88;
    rv1 = t7;
    if (t6 <= t7) {
        p0->m18->m2C = (t6 + -1);
        rv1 = (t6 + -1);
    }
    t8 = p0->m18;
    t9 = p0->m18->m2C;
    return t9;
}
