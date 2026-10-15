#include "types.h"

f32 VariantGetFloat_15f740(s32);
s32 VariantGetInt_15f780(s32, s32, u8 *);
extern u8 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdEntrySetParams_402fb0(s64 *arg0) {
    u8 *o;
    s32 n;
    s32 k;
    s32 r;
    u8 *e;
    u8 *f;

    o = D_004830F8;
    n = *(s16 *)(o + 0x7C);
    if (n <= 0) {
        return 1;
    }
    k = D_004830FC - 1;
    if (k >= n) {
        return 1;
    }
    e = *(u8 **)(o + 0x8C) + k * 0x90;
    r = VariantGetInt_15f780((s32)arg0++, k, o);
    if (r < 0 || r >= 3) {
        return 1;
    }
    f = e + r * 0x14 + 0x40;
    *(s16 *)f = VariantGetFloat_15f740((s32)arg0++);
    *(f32 *)(f + 4) = VariantGetFloat_15f740((s32)arg0++);
    *(f32 *)(f + 8) = VariantGetFloat_15f740((s32)arg0++);
    *(f32 *)(f + 0xC) = VariantGetFloat_15f740((s32)arg0++);
    *(f32 *)(f + 0x10) = VariantGetFloat_15f740((s32)arg0++);
    return 1;
}
