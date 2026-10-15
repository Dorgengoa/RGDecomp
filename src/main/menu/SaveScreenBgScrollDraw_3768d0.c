/* PARK s17d try1: length 0x228 vs retail 0x230, 2 words short. */
#include "types.h"

extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern void GsPktSetupUiDrawState_2932b0(s32);
extern s32 GetPauseStep_2f6660(void);
extern s32 SaveIsBusy_376b00(void);
extern u8 D_00463B20[0x400];
extern u8 D_004831F4;
extern f32 D_00483210;

void SaveScreenBgScrollDraw_3768d0(s32 arg0, f32 fparg0)
{
    f32 x;
    f32 y;
    s32 h;
    s32 w;
    s32 sess;
    s32 tex;

    if (arg0 == 0) {
        return;
    }
    sess = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(sess);
    h = DrawEnvGetHeight_1451d0(sess);
    tex = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), &(*(u8 *)D_00463B20), -1);
    if (tex == 0) {
        return;
    }
    GsPktSetupUiDrawState_2932b0(arg0);
    GsPktSetTexFilter_13e3d0(arg0, 0);
    GsPktOpenPrim_13f730(arg0, 6);
    GsPktSetTexture_13ec00(arg0, tex);
    GsPktSetRGBAQ_13ee40(arg0, 0x80, 0x80, 0x80, (s32)(128.0f * fparg0));
    if ((GetPauseStep_2f6660() == 0 || SaveIsBusy_376b00() != 0) && D_004831F4 == 0) {
        D_00483210 += 0.5f;
    }
    if (256.0f <= D_00483210) {
        D_00483210 -= 256.0f;
    }
    for (x = D_00483210 - 256.0f; x < (f32)w; x += 256.0f) {
        for (y = D_00483210 - 256.0f; y < (f32)h; y += 256.0f) {
            GsPktSetUV_13ed60(arg0, 0, 0);
            GsPktSetXYZf_13f060(arg0, x, y, 0.0f);
            GsPktSetUV_13ed60(arg0, 0x100, 0x100);
            GsPktSetXYZf_13f060(arg0, 256.0f + x, 256.0f + y, 0.0f);
        }
    }
    GsPktClose_13f5b0(arg0);
}
