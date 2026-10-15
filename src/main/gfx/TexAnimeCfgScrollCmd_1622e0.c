#include "types.h"

extern f32 VariantGetFloat_15f740(s32);
extern volatile f32 D_0047D24C;
extern s8 D_00495E70[16];
extern s16 D_00495E88[16];
extern s16 D_00495E8A[16];
extern s16 D_00495E8C[16];
extern s16 D_00495E8E[16];
extern s16 D_00495E98[16];
extern s16 D_00495E9A[16];

s32 TexAnimeCfgScrollCmd_1622e0(s64 *arg0)
{
    f32 f20;
    f32 f1;
    f32 f0;
    f32 d3;
    f32 d2;
    f32 k;
    s32 i2;

    if (D_00495E70[0] == 1) {
        f20 = 16.0f * VariantGetFloat_15f740((s32)arg0++);
        f1 = 16.0f * VariantGetFloat_15f740((s32)arg0);
        D_00495E8C[0] = (s32)((f32)(D_00495E88[0] - 0x10) / f20);
        D_00495E8E[0] = (s32)((f32)(D_00495E8A[0] - 0x10) / f1);
    } else if (D_00495E70[0] == 2) {
        f20 = VariantGetFloat_15f740((s32)arg0++);
        f0 = VariantGetFloat_15f740((s32)arg0);
        k = 10000;
        D_00495E8C[0] = (s32)f20;
        d3 = f20 - (f32)(s32)f20;
        D_00495E8E[0] = (s32)f0;
        d2 = f0 - (f32)(s32)f0;
        D_00495E98[0] = (s32)(k * d3);
        D_00495E9A[0] = (s32)(k * d2);
        d3 = (d3 < 0.0f) ? -d3 : d3;
        if (d3 < D_0047D24C) {
            D_00495E98[0] = 10000;
        }
        d2 = (d2 < 0.0f) ? -d2 : d2;
        if (d2 < D_0047D24C) {
            D_00495E9A[0] = 10000;
        }
    } else {
        return 0;
    }
    return 1;
}
