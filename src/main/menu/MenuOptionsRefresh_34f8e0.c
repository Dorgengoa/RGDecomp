#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 MenuOptionsValueHighlight_34fa30(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Obj1 {
    u8 pad000[0x12];
    s16 m12;
    u8 pad014[0x6];
    s16 m1A;
    u8 pad01C[0x4];
    s16 m20;
    s16 m22;
    u8 pad024[0x2];
    s16 m26;
    s16 m28;
    s16 m2A;
    s16 m2C;
};

s32 MenuOptionsRefresh_34f8e0(void)
{
    struct Obj0 *r0;
    struct Obj1 * t0;
    s16 t1;
    s32 r1;
    struct Obj1 * t2;
    s16 t3;
    s32 r2;
    struct Obj1 * t4;
    s16 t5;
    s32 r3;
    struct Obj1 * t6;
    s16 t7;
    s32 r4;
    struct Obj1 * t8;
    s16 t9;
    s32 r5;
    struct Obj1 * t10;
    s16 t11;
    s32 r6;
    struct Obj1 * t12;
    s16 t13;
    s32 r7;
    struct Obj1 * t14;
    s16 t15;
    s32 r8;
    struct Obj1 * t16;
    s16 t17;
    s32 r9;
    struct Obj1 * t18;
    s16 t19;
    s32 r10;

    r0 = GetGameData_1fede0();
    t0 = r0->m0C;
    t1 = r0->m0C->m1A;
    r1 = MenuOptionsValueHighlight_34fa30((t1 & 1), 1, 0, 0x1B7, 0x1B8);
    t2 = r0->m0C;
    t3 = r0->m0C->m22;
    r2 = MenuOptionsValueHighlight_34fa30(t3, 1, 0, 0x1B9, 0x1BA);
    t4 = r0->m0C;
    t5 = r0->m0C->m12;
    r3 = MenuOptionsValueHighlight_34fa30(t5, 0, 1, 0x1BB, 0x1BC);
    t6 = r0->m0C;
    t7 = r0->m0C->m26;
    r4 = MenuOptionsValueHighlight_34fa30(t7, 1, 0, 0x1BD, 0x1BE);
    t8 = r0->m0C;
    t9 = r0->m0C->m2A;
    r5 = MenuOptionsValueHighlight_34fa30(t9, 1, 0, 0x1BF, 0x1C0);
    t10 = r0->m0C;
    t11 = r0->m0C->m28;
    r6 = MenuOptionsValueHighlight_34fa30(t11, 1, 0, 0x1C1, 0x1C2);
    t12 = r0->m0C;
    t13 = r0->m0C->m1A;
    r7 = MenuOptionsValueHighlight_34fa30((t13 & 2), 0, 2, 0x1C3, 0x1C4);
    t14 = r0->m0C;
    t15 = r0->m0C->m1A;
    r8 = MenuOptionsValueHighlight_34fa30((t15 & 4), 0, 4, 0x1C5, 0x1C6);
    t16 = r0->m0C;
    t17 = r0->m0C->m2C;
    r9 = MenuOptionsValueHighlight_34fa30(t17, 1, 0, 0x1C7, 0x1C8);
    t18 = r0->m0C;
    t19 = r0->m0C->m20;
    r10 = MenuOptionsValueHighlight_34fa30(t19, 1, 0, 0x1C9, 0x1CA);
    return 1;
}
