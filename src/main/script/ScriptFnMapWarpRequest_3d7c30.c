#include "types.h"

u8 MapWarpRequest_285d80(s32, u8 *, u8 *, f32, f32, f32, f32);
void VariantSetS32_36f040(s32, s32, s32);
f32 VariantGetFloat_36f7a0(s32);
s16 VariantGetS16_36fcc0(s32);
extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnMapWarpRequest_3d7c30(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 t;
    f32 a;
    f32 b;
    f32 c;
    f32 d;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0) {
        return;
    }
    if (D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 < 5) {
        return;
    }
    t = VariantGetS16_36fcc0(arg3);
    a = VariantGetFloat_36f7a0(arg3 + 0x38);
    b = VariantGetFloat_36f7a0(arg3 + 0x70);
    c = VariantGetFloat_36f7a0(arg3 + 0xA8);
    d = VariantGetFloat_36f7a0(arg3 + 0xE0);
    {
        u8 buf1[12] = {0};
        u8 buf2[12] = {0};
        VariantSetS32_36f040(arg0, MapWarpRequest_285d80(t, buf1, buf2, a, b, c, d), 1);
    }
}
