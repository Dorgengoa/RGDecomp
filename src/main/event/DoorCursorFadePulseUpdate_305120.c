#include "types.h"
#pragma divbyzerocheck on
typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Obj {
    u8 pad0[0xC];
    f32 mC;
    f32 m10;
    f32 m14[2];
    s16 m1C;
    s16 m1E;
    s16 m20;
    s16 m22;
    f32 m24[12];
    f32 m54[12];
    f32 m84;
    f32 m88;
    f32 m8C;
} Obj;

extern void VecLinearCombine_1cb8b0(V4 *, V4 *, V4 *, f32, f32);
extern f32 VecLengthSq_1cb470(V4 *);
extern void VecScaleToLength_1cb510(V4 *, V4 *, f32);
extern void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
extern const f32 D_0047DAA0 __attribute__((section(".sdata")));
extern const f32 D_0047DAA8 __attribute__((section(".sdata")));
extern const f32 D_0047DAAC __attribute__((section(".sdata")));
extern const f32 D_0047DA6C __attribute__((section(".sdata")));
extern const f32 D_0047D5D0 __attribute__((section(".sdata")));

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 16; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

void DoorCursorFadePulseUpdate_305120(Obj *p)
{
    V4 a;
    V4 b;
    s32 i;
    s32 k;
    s32 j;

    switch (p->m1E) {
    case 1:
        if (p->m22 == 0) {
            p->m84 = 0.0f;
            p->m88 = 0.0f;
            p->m8C = 1.0f;
            for (i = 0; i < 2; i++) {
                p->m14[i] = 0.0f;
            }
            p->m1C = 0;
            for (i = 0; i < 12; i++) {
                p->m24[i] = 0.0f;
                p->m54[i] = 0.0f;
            }
        }
        if (!(p->m84 < 128.0f)) {
            p->m1E = 2;
        }
        break;
    case 2:
        if (!(p->m88 < 128.0f)) {
            p->m1E = 3;
        }
        break;
    case 3:
        if (p->m88 <= 0.0f) {
            p->m1E = 4;
            p->m22 = 0;
        }
        break;
    case 4:
        if (!(p->m22 < 30)) {
            p->m1E = 2;
            p->m22 = 0;
            p->m88 = 0.0f;
            p->m8C = 1.0f;
        }
        break;
    case 5:
        if (p->m84 <= 0.0f) {
            p->m1E = 6;
        }
        break;
    case 7:
        if (p->m84 <= 0.0f) {
            p->m1E = 0;
        }
        break;
    case 6:
        break;
    case 0:
    default:
        p->m1E = 0;
        break;
    }
    switch (p->m1E) {
    case 1:
        p->m84 = p->m84 + D_0047DAA8;
        p->m88 = 0.0f;
        p->m88 = 1.0f;
        break;
    case 2:
        p->m84 = 128.0f;
        p->m88 = p->m88 + D_0047DAAC;
        break;
    case 3:
        p->m84 = 128.0f;
        p->m88 = p->m88 - D_0047DAA8;
        p->m8C = p->m8C + D_0047DAA0;
        break;
    case 4:
        p->m84 = 128.0f;
        p->m88 = 0.0f;
        break;
    case 5:
    case 7:
        p->m88 = p->m88 - *(f32 *)&D_0047DAA8;
        p->m84 = p->m84 - *(f32 *)&D_0047DAA8;
        break;
    case 0:
    case 6:
    default:
        p->m84 = 0.0f;
        p->m88 = 0.0f;
        return;
    }
    if (p->m84 < 0.0f) {
        p->m84 = 0.0f;
    }
    if (!(p->m84 <= 128.0f)) {
        p->m84 = 128.0f;
    }
    if (p->m88 < 0.0f) {
        p->m88 = 0.0f;
    }
    if (!(p->m88 <= 128.0f)) {
        p->m88 = 128.0f;
    }
    ZERO16(&a)
    a.y = p->m10;
    ZERO16(&b)
    b.y = p->mC;
    VecLinearCombine_1cb8b0(&a, &a, &b, 1.0f, D_0047DA6C);
    if (!(VecLengthSq_1cb470(&a) <= 1.0f)) {
        VecScaleToLength_1cb510(&a, &a, 1.0f);
    }
    VecAdd_1cbdc0(&b, &b, &a);
    p->m10 = a.y;
    p->mC = b.y;
    if (p->m1E != 4 && p->m1E != 6) {
        k = p->m22 % 10;
        for (i = 0; i < p->m1C; i++) {
            p->m14[i] = p->m14[i] - D_0047D5D0;
            if (p->m14[i] < 0.0f) {
                p->m14[i] = 0.0f;
            }
        }
        if (k == 0) {
            if (p->m1C < 2) {
                p->m14[p->m1C] = 4.0f;
                p->m1C++;
            }
        }
        for (i = 0; i < 12; i++) {
            p->m24[i] = p->m24[i] - 15.0f;
            if (p->m24[i] < 0.0f) {
                p->m24[i] = 0.0f;
            }
        }
        if (k % 3 == 1) {
            j = k / 3;
            p->m24[j] = 128.0f;
            p->m54[j] = p->m14[p->m1C - 1];
        }
    }
    p->m20++;
    p->m22++;
    if (!(p->m22 < 360)) {
        p->m22 = 0;
    }
}
