#include "types.h"

extern void * UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D278;
extern s32 D_00484710;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    s16 m00;
    s16 m02;
    u8 pad004[0x1C];
    s16 m20;
    s16 m22;
};

struct Obj1 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    u8 pad008[0x4];
    s16 m0C;
    s16 m0E;
    u8 pad010[0x10];
    s16 m20;
    s16 m22;
    s16 m24;
    s16 m26;
    u8 pad028[0x4];
    s16 m2C;
    s16 m2E;
};

struct Obj2 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    u8 pad008[0x4];
    s16 m0C;
    s16 m0E;
    u8 pad010[0x10];
    s16 m20;
    s16 m22;
    s16 m24;
    s16 m26;
    u8 pad028[0x4];
    s16 m2C;
    s16 m2E;
};

s32 TransMenuItemTabLayoutMaybe_37f0c0(s32 p0)
{
    s32 t0;
    struct Obj2 *r0;
    s32 t1;
    struct Obj1 *r1;
    s32 rv7;
    s32 t2;
    struct Obj0 *r2;
    s32 rv6;
    f32 t3;
    s32 t4;
    s32 rv5;
    s32 rv4;

    t0 = D_00484710;
    r0 = UiGetWidgetSprite_28fe10(t0, 0x75FB, 0);
    if (r0 == 0) {
        return 0;
    }
    t1 = D_00484710;
    r1 = UiGetWidgetSprite_28fe10(t1, 0x75FC, 0);
    if (r1 == 0) {
        rv7 = 0;
    } else {
        t2 = D_00484710;
        r2 = UiGetWidgetSprite_28fe10(t2, 0x75FD, 0);
        rv6 = 1;
        if (r2 == 0) {
            rv6 = 0;
        } else {
            r2->m20 = -0x10;
            r2->m00 = -0x10;
            t3 = D_0047D278;
            r2->m02 = 0x3C;
            r2->m22 = 0x66;
            t4 = D_00484710;
            UiSetWidgetAlpha_2907a0(t4, 0x75FD, t3);
            r1->m00 = -0x1A;
            r0->m00 = -0x1A;
            r1->m20 = -0x18;
            r0->m20 = -0x18;
            if (p0 == 0) {
                r0->m0C = 0x2A;
                r0->m04 = 0x2A;
                r0->m0E = 0x2C;
                r0->m06 = 0x2C;
                r0->m2E = 0;
                r0->m26 = 0;
                r0->m2C = 0;
                r0->m24 = 0;
                r0->m02 = 0x5C;
                r1->m2E = 0;
                r1->m06 = 0;
                r1->m0C = 0;
                r1->m04 = 0;
                r1->m2C = 0x1E;
                r1->m24 = 0x1E;
                r1->m2E = 0x2C;
                r1->m26 = 0x2C;
                r1->m22 = 0x32;
                rv5 = 0x32;
            } else {
                rv4 = 1;
                if (p0 == 1) {
                    r0->m2C = 0x1E;
                    r0->m24 = 0x1E;
                    r0->m2E = 0x2C;
                    r0->m26 = 0x2C;
                    r0->m0E = 0;
                    r0->m06 = 0;
                    r0->m0C = 0;
                    r0->m04 = 0;
                    r0->m22 = 0x5C;
                    r1->m0C = 0x2A;
                    r1->m04 = 0x2A;
                    r1->m0E = 0x2C;
                    r1->m06 = 0x2C;
                    r1->m2E = 0;
                    r1->m26 = 0;
                    r1->m2C = 0;
                    r1->m24 = 0;
                    r1->m02 = 0x32;
                    rv4 = 0x32;
                }
                rv5 = rv4;
            }
            rv6 = 1;
        }
        rv7 = rv6;
    }
    return rv7;
}
