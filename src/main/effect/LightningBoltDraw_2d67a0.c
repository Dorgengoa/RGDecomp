#include "types.h"


extern void TrailRibbonDraw_32c370(void *, s32, s32, f32);
extern void TrailRibbonSetColor_32c730(void *, f32, f32, f32, f32);
extern void TrailRibbonSetNodes_32c750(void *, void *, s32);
extern void sceVu0CopyVector(void *, void *);

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0x4];
    f32 unk98;
    u8 pad9C[4];u8 data[0x20];
    s8 unkC0;
    u8 padC1[0x1];
    s16 unkC2;
} T2d67a0_arg0;

void LightningBoltDraw_2d67a0(T2d67a0_arg0 *arg0, s32 arg1, s32 arg2)
{
    u8 sp70[0x600];
    f32 var_f21;
    s32 count;
    s32 i;
    s32 idx8;
    f32 idxF;
    u8 *elem;

    if (arg0->unkC2 > 0) {
        TrailRibbonSetColor_32c730(arg0->data, 128.0f, 128.0f, 128.0f,
                     128.0f * arg0->unk90);
        var_f21 = 0.0f;
        if (arg0->unkC0 != 0) {
            var_f21 = 32.0f;
        }
        i = 0;
        while (i < (count=arg0->unkC2)) {
            elem = sp70 + (i * 0x60);
            sceVu0CopyVector(elem, (u8 *)arg0 + (i * 0x10));
            idx8 = i * 8;
            *(f32 *)(elem + 0x50) = arg0->unk98;
            idxF = (f32)idx8;
            i += 1;
            *(f32 *)(elem + 0x30) = var_f21;
            *(f32 *)(elem + 0x34) = idxF;
            *(f32 *)(elem + 0x38) = 1.0f;
            *(f32 *)(elem + 0x40) = 32.0f + var_f21;
            *(f32 *)(elem + 0x44) = idxF;
            *(f32 *)(elem + 0x48) = 1.0f;

        }
        TrailRibbonSetNodes_32c750(arg0->data, sp70, count);
        TrailRibbonDraw_32c370(arg0->data, arg1, arg2, 1.0f);
    }
}
