#include "types.h"
#pragma opt_common_subs off

extern void ScreenFadeCaptureFrame_1cf550(s32);
extern s32 ScriptGetInt_2490f0(void);
extern s32 MenuWinGet_2653e0(s32);
extern void MenuWinSetAlphaTest_26c250(s32, s32);
extern void MenuWinSetAlphaBlend_26c260(s32, s32);
extern void MenuWinSetUvRect_26c300(s32, s32, s32, s32, s32);
extern void MenuWinSetSize_26c320(s32, s32, s32);
extern void MenuWinSetColor_26c380(s32, f32 *);
extern void MenuWinSetPos_26c3b0(s32, f32 *);
extern void MenuWinSetTexFilter_26c3c0(s32, s32);
extern void MenuWinSetDrawMode_26c3e0(s32, s32);
extern void MenuWinSetUseCaptureTex_26c400(s32, s32);
extern f32 D_0047E830;
extern f32 D_0047E834;
extern f32 D_0047E838;
extern f32 D_0047E83C;
extern f32 D_0047E840;
extern f32 D_0047E844;
extern f32 D_0047E848;
extern f32 D_0047E84C;
extern s32 *gEventContext;

s32 EvCmdMenuWinShowScreenCapture_243990(void)
{
    f32 a[4];
    f32 *qa = a;
    f32 b[4];
    f32 *qb = b;
    s32 h;

    h = MenuWinGet_2653e0(ScriptGetInt_2490f0());
    if (h == 0) {
        return 0;
    }
    qa[0] = D_0047E830;
    qa[1] = D_0047E834;
    qa[2] = D_0047E838;
    qa[3] = D_0047E83C;
    qb[0] = D_0047E840;
    qb[1] = D_0047E844;
    qb[2] = D_0047E848;
    qb[3] = D_0047E84C;
    MenuWinSetDrawMode_26c3e0(h, 0);
    MenuWinSetPos_26c3b0(h, a);
    MenuWinSetColor_26c380(h, b);
    MenuWinSetAlphaBlend_26c260(h, 0);
    MenuWinSetAlphaTest_26c250(h, 0);
    MenuWinSetSize_26c320(h, 0x200, 0x1C0);
    MenuWinSetUvRect_26c300(h, 0, 0, 0x200, 0x1C0);
    MenuWinSetUseCaptureTex_26c400(h, 1);
    MenuWinSetTexFilter_26c3c0(h, 0);
    ScreenFadeCaptureFrame_1cf550(*gEventContext);
    return 1;
}
