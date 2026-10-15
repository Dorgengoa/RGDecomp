#include "types.h"

extern s32 UnitBaseResetStatsToBase_3b82e0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    s32 m1C;
    s32 m20;
    u16 m24;
    s16 m26;
    s16 m28;
    s16 m2A;
    u16 m2C;
    s16 m2E;
    u16 m30;
    s16 m32;
    u16 m34;
    s16 m36;
    u16 m38;
    s16 m3A;
    f32 m3C;
    f32 m40;
    f32 m44;
    f32 m48;
    f32 m4C;
    f32 m50;
    u8 pad054[0x1E8];
    s16 m23C;
    s16 m23E;
    f32 m240;
    f32 m244;
    f32 m248;
    f32 m24C;
    f32 m250;
    f32 m254;
    f32 m258;
    f32 m25C;
};

s32 UnitResetStatsToBase_3be5c0(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;
    u16 t1;
    u16 t2;
    u16 t3;
    u16 t4;
    s16 t5;
    u16 t6;
    f32 t7;
    f32 t8;
    f32 t9;
    f32 t10;
    f32 t11;
    f32 t12;
    f32 t13;
    s32 l1;
    s16 t14;
    s32 l2;
    s16 t15;
    s32 l3;
    s16 t16;
    s32 l4;
    s16 t17;
    s32 l5;
    s16 t18;

    r0 = UnitBaseResetStatsToBase_3b82e0();
    if ((r0 & 0xFF) == 0) {
        return 0;
    }
    t0 = p0->m1C;
    p0->m20 = t0;
    t1 = p0->m24;
    p0->m26 = t1;
    t2 = p0->m30;
    p0->m32 = t2;
    t3 = p0->m34;
    p0->m36 = t3;
    t4 = p0->m38;
    p0->m3A = t4;
    p0->m28 = 0;
    p0->m2A = 0;
    t5 = p0->m23C;
    p0->m23E = t5;
    t6 = p0->m2C;
    p0->m2E = t6;
    t7 = p0->m240;
    p0->m244 = t7;
    t8 = p0->m248;
    p0->m24C = t8;
    t9 = p0->m250;
    p0->m254 = t9;
    t10 = p0->m258;
    p0->m25C = t10;
    t11 = p0->m3C;
    p0->m40 = t11;
    t12 = p0->m44;
    p0->m48 = t12;
    t13 = p0->m4C;
    p0->m50 = t13;
    l1 = 0;
    do {
        t14 = *(s16 *)((u8 *)p0 + (l1 << 2) + 0x264);
        *(s16 *)((u8 *)p0 + (l1 << 2) + 0x266) = t14;
        l1 = (l1 + 1);
    } while (l1 < 5);
    l2 = 0;
    do {
        t15 = *(s16 *)((u8 *)p0 + (l2 << 2) + 0x54);
        *(s16 *)((u8 *)p0 + (l2 << 2) + 0x56) = t15;
        l2 = (l2 + 1);
    } while (l2 < 5);
    l3 = 0;
    do {
        t16 = *(s16 *)((u8 *)p0 + (l3 << 2) + 0x68);
        *(s16 *)((u8 *)p0 + (l3 << 2) + 0x6A) = t16;
        l3 = (l3 + 1);
    } while (l3 < 8);
    l4 = 1;
    do {
        t17 = *(s16 *)((u8 *)p0 + (l4 << 2) + 0x84);
        *(s16 *)((u8 *)p0 + (l4 << 2) + 0x86) = t17;
        l4 = (l4 + 1);
    } while (l4 < 8);
    l5 = 0;
    do {
        t18 = *(s16 *)((u8 *)p0 + (l5 << 2) + 0xA8);
        *(s16 *)((u8 *)p0 + (l5 << 2) + 0xAA) = t18;
        l5 = (l5 + 1);
    } while (l5 < 4);
    return 1;
}
