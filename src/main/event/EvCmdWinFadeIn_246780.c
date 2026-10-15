#include "types.h"

extern s32 ScriptGetInt_2490f0(s64 * arg0);
extern s32 MenuWinGet_2653e0(s32 arg0);
extern void MenuWinFadeColorToInt_26c1c0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void MenuWinSetBlendMode_26c270(s32 arg0, s32 arg1);
extern void MenuWinSetSize_26c320(s32 arg0, s32 arg1, s32 arg2);
extern void MenuWinSetColorInt_26c330(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void MenuWinSetPosXyz_26c390(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
extern void MenuWinSetDrawLayer_26c3d0(s32 arg0, s32 arg1);
extern void MenuWinSetDrawMode_26c3e0(s32 arg0, s32 arg1);
extern void MenuWinSetActive_26c3f0(s32 arg0, s32 arg1);
extern void MenuWinInit_26c450(s32 arg0);

s32 EvCmdWinFadeIn_246780(s64 *arg0, s32 arg1)
{
    s32 k;
    s32 c;
    s32 b;
    s32 t;
    s32 a;

    k = ScriptGetInt_2490f0(arg0++);
    t = MenuWinGet_2653e0(7);
    MenuWinInit_26c450(t);
    MenuWinSetDrawMode_26c3e0(t, 0);
    MenuWinSetBlendMode_26c270(t, 1);
    MenuWinSetPosXyz_26c390(t, 256.0f, 224.0f, 0.0f);
    MenuWinSetSize_26c320(t, 0x200, 0x1C0);
    MenuWinSetActive_26c3f0(t, 1);
    MenuWinSetDrawLayer_26c3d0(t, 2);
    switch (arg1) {
    case 1:
        MenuWinSetColorInt_26c330(t, 0, 0, 0, 0x80);
        MenuWinFadeColorToInt_26c1c0(t, 0, 0, 0, 0, k);
        break;
    case 4:
        a = ScriptGetInt_2490f0(arg0++);
        b = ScriptGetInt_2490f0(arg0++);
        c = ScriptGetInt_2490f0(arg0);
        MenuWinSetColorInt_26c330(t, a, b, c, 0x80);
        MenuWinFadeColorToInt_26c1c0(t, a, b, c, 0, k);
        break;
    }
    return 1;
}
