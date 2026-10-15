#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

extern void GsPktSetTexture_13ec00(s32, u8 *);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32 GetDrawCtxNameTable_15de40();
extern void MinimapTileIndexToXY_323290(u8 *, u8, s32 *, s32 *);
extern void EntryListSetTexSize_323350(u8 *, s16, s16);
extern s32 EntryGetTileSize_323ad0(s32);

s32 MinimapDrawTile_328f10(u8 *self, s32 arg1, s32 arg2, s32 tgt, s8 *info, s32 x, s32 y) {
    u8 *w; u8 *tex; s32 sz; s32 sp8C; s32 sp88; s32 a; s32 b; s32 c; s32 d; s32 b1; s32 a1; s32 c1; s32 d1;

    if (info == 0) return 0;
    if (tgt == 0) return 0;
    if (arg1 == 0) return 0;
    w = self + 0x12C;
    if (w == 0) return 0;
    sz = EntryGetTileSize_323ad0(arg1);
    if (info[0] < 0) return 0;
    if (GetDrawCtxNameTable_15de40() == 0) return 0;
    tex = ((u8 **)(self + 0x84))[info[0]];
    if (tex == 0) return 0;
    EntryListSetTexSize_323350(w, *(s16 *)(tex + 2), *(s16 *)(tex + 4));
    MinimapTileIndexToXY_323290(w, ((u8 *)info)[1], &sp8C, &sp88);
    if (((u8 *)info)[2] == 0) {
        GsPktOpenPrim_13f730(tgt, 6);
    } else {
        GsPktOpenPrim_13f730(tgt, 3);
    }
    GsPktSetTexture_13ec00(tgt, tex);
    { s32 k = 0x80; s32 t = tgt; GsPktSetRGBAQ_13ee40(t, k, k, k, 0x82); }
    switch (((u8 *)info)[2]) {
    case 0:
        GsPktSetUV_13ed60(tgt, sp8C, sp88);
        GsPktSetXYZPixel_13f110(tgt, sz * x, sz * y, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz, sp88 + sz);
        GsPktSetXYZPixel_13f110(tgt, sz * (x + 1), sz * (y + 1), 0);
        break;
    case 1:
        GsPktSetUV_13ed60(tgt, sp8C + sz - 1, sp88);
        b1 = sz * y; a1 = sz * x;
        GsPktSetXYZPixel_13f110(tgt, a1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz, sp88 + sz);
        c1 = sz * (x + 1);
        GsPktSetXYZPixel_13f110(tgt, c1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88);
        d1 = sz * (y + 1);
        GsPktSetXYZPixel_13f110(tgt, a1, d1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88);
        GsPktSetXYZPixel_13f110(tgt, a1, d1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz - 1, sp88 + sz);
        GsPktSetXYZPixel_13f110(tgt, c1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88 + sz);
        GsPktSetXYZPixel_13f110(tgt, c1, d1, 0);
        break;
    case 2:
        GsPktSetUV_13ed60(tgt, sp8C + sz - 1, sp88 + sz - 1);
        b1 = sz * y; a1 = sz * x;
        GsPktSetXYZPixel_13f110(tgt, a1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88 + sz - 1);
        c1 = sz * (x + 1);
        GsPktSetXYZPixel_13f110(tgt, c1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz - 1, sp88);
        d1 = sz * (y + 1);
        GsPktSetXYZPixel_13f110(tgt, a1, d1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz - 1, sp88);
        GsPktSetXYZPixel_13f110(tgt, a1, d1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88 + sz - 1);
        GsPktSetXYZPixel_13f110(tgt, c1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88);
        GsPktSetXYZPixel_13f110(tgt, c1, d1, 0);
        break;
    case 3:
        GsPktSetUV_13ed60(tgt, sp8C, sp88 + sz - 1);
        b1 = sz * y; a1 = sz * x;
        GsPktSetXYZPixel_13f110(tgt, a1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88);
        c1 = sz * (x + 1);
        GsPktSetXYZPixel_13f110(tgt, c1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz, sp88 + sz - 1);
        d1 = sz * (y + 1);
        GsPktSetXYZPixel_13f110(tgt, a1, d1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz, sp88 + sz - 1);
        GsPktSetXYZPixel_13f110(tgt, a1, d1, 0);
        GsPktSetUV_13ed60(tgt, sp8C, sp88);
        GsPktSetXYZPixel_13f110(tgt, c1, b1, 0);
        GsPktSetUV_13ed60(tgt, sp8C + sz, sp88);
        GsPktSetXYZPixel_13f110(tgt, c1, d1, 0);
        break;
    }
    GsPktClose_13f5b0(tgt);
    return 1;
}
