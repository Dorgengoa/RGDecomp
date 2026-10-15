#include "types.h"

extern s32 DListNodeInit_42ec10(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s64 m10;
    s64 m18;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s16 m30;
    s16 m32;
    s16 m34;
    s16 m36;
    s32 m38;
    s32 m3C;
    s16 m40;
    s16 m42;
    s32 m44;
};

struct Obj0 *CharaTableObjCtor_224190(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = DListNodeInit_42ec10(p0);
    p0->m20 = 0;
    p0->m36 = 0;
    p0->m10 = 0;
    p0->m18 = 0;
    p0->m24 = 0;
    p0->m30 = 0;
    p0->m28 = 0;
    p0->m32 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m20 = 0;
    p0->m36 = 0;
    p0->m10 = 0;
    p0->m18 = 0;
    p0->m24 = 0;
    p0->m30 = 0;
    p0->m28 = 0;
    p0->m32 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3C = 0;
    p0->m40 = 0;
    p0->m44 = 0x3F800000;
    p0->m42 = 0;
    r1 = DListNodeInit_42ec10(p0);
    p0->m20 = 0;
    p0->m36 = 0;
    p0->m10 = 0;
    p0->m18 = 0;
    p0->m24 = 0;
    p0->m30 = 0;
    p0->m28 = 0;
    p0->m32 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3C = 0;
    p0->m40 = 0;
    p0->m44 = 0x3F800000;
    p0->m42 = 0;
    return p0;
}
