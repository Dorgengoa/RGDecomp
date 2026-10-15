#include "types.h"

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 D_0047D1FC;
extern f32 D_0047DC08;
extern f32 D_0047DC0C;
extern f32 D_0047DC10;
extern f32 D_0047DC14;
extern f32 D_0047DC18;
extern f32 D_0047DC1C;

typedef struct {
    u8 pad0[0x10];
    f32 x10;
    f32 x14;
    f32 x18;
    u8 pad1C[0x14];
    s32 x30;
} Key;

typedef struct {
    u8 pad0[0x3C];
    s32 x3C;
    u8 pad40[0x10];
    f32 x50;
    f32 x54;
    f32 x58;
    u8 pad5C[4];
    f32 x60;
    f32 x64;
    f32 x68;
    u8 pad6C[4];
    f32 x70;
    f32 x74;
    f32 x78;
    s32 x7C;
    u8 pad80[0x20];
    f32 xA0;
    f32 xA4;
    f32 xA8;
    u8 padAC[0x44];
    f32 xF0;
    u8 padF4[4];
    f32 xF8;
    f32 xFC;
    u8 pad100[0x70];
    f32 x170;
    f32 x174;
    f32 x178;
} Cam;

s32 EventCameraCmdOrbitMoveLinear_255d20(Key *arg0, Cam *arg1) {
    f32 d;
    f32 a;
    f32 lim;
    f32 d2;

    if (arg1->x3C >= arg0->x30) {
        if (arg1->x7C != 0) {
            arg1->xA0 = arg0->x10;
            arg1->xA4 = arg0->x14;
            arg1->xA8 = arg0->x18;
        } else {
            arg1->x70 = arg0->x10;
            arg1->x74 = arg0->x14;
            arg1->x78 = arg0->x18;
            arg1->x50 = arg1->x60 + arg1->x78 * Sinf_128fd0(arg1->x70);
            arg1->x54 = arg1->x74 + arg1->x64;
            arg1->x58 = arg1->x68 + arg1->x78 * Cosf_128d30(arg1->x70);
        }
        arg1->x3C = 0;
        return 0;
    }
    if (arg1->x3C <= 0) {
        if (arg1->x7C != 0) {
            d = arg0->x10 - arg1->xA0;
        } else {
            d = arg0->x10 - arg1->x70;
        }
        if (d > D_0047D1FC) {
            d -= D_0047DC0C;
        } else if (d <= D_0047DC08) {
            d += D_0047DC0C;
        }
        arg1->xF0 = d / (f32)arg0->x30;
        arg1->xF8 = (arg0->x14 - arg1->x74) / (f32)arg0->x30;
        arg1->xFC = (arg0->x18 - arg1->x78) / (f32)arg0->x30;
        arg1->x170 = arg1->xF0;
        arg1->x174 = arg1->xF8;
        arg1->x178 = arg1->xFC;
    } else if (arg1->x7C != 0) {
        d2 = arg1->xF0;
        a = arg1->xA0;
        lim = D_0047D1FC;
        arg1->xA0 = a + d2;
        if (arg1->xA0 > lim) {
            arg1->xA0 -= D_0047DC0C;
        } else if (arg1->xA0 <= D_0047DC10) {
            arg1->xA0 += D_0047DC14;
        }
        arg1->xA4 += arg1->xF8;
        arg1->xA8 += arg1->xFC;
    } else {
        d2 = arg1->xF0;
        a = arg1->x70;
        lim = D_0047D1FC;
        arg1->x70 = a + d2;
        if (arg1->x70 > lim) {
            arg1->x70 -= D_0047DC14;
        } else if (arg1->x70 <= D_0047DC18) {
            arg1->x70 += D_0047DC1C;
        }
        arg1->x74 += arg1->xF8;
        arg1->x78 += arg1->xFC;
        arg1->x50 = arg1->x60 + arg1->x78 * Sinf_128fd0(arg1->x70);
        arg1->x54 = arg1->x74 + arg1->x64;
        arg1->x58 = arg1->x68 + arg1->x78 * Cosf_128d30(arg1->x70);
    }
    arg1->x3C++;
    return 1;
}
