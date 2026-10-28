/* rgp:protos */
#define RGP_SELF_EvCmdWinFadeOut_246600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdWinFadeOut_246600(s64 *arg0, s32 arg1)
{
    s32 id;
    s32 h;
    s32 c;
    s32 b;
    s32 a;

    id = ScriptGetInt_2490f0((s32)arg0++);
    h = ((s32)MenuWinGet_2653e0(7));
    MenuWinInit_26c450(h);
    MenuWinSetDrawMode_26c3e0(h, 0);
    MenuWinSetBlendMode_26c270(h, 1);
    MenuWinSetPosXyz_26c390(h, 256.0f, 224.0f, 0.0f);
    MenuWinSetSize_26c320(h, 0x200, 0x1C0);
    MenuWinSetActive_26c3f0(h, 1);
    MenuWinSetDrawLayer_26c3d0(h, 2);
    switch (arg1) {
    case 1:
        MenuWinSetColorInt_26c330(h, 0, 0, 0, 0);
        MenuWinFadeColorToInt_26c1c0(h, 0, 0, 0, 0x80, id);
        break;
    case 4:
        a = ScriptGetInt_2490f0((s32)arg0++);
        b = ScriptGetInt_2490f0((s32)arg0++);
        c = ScriptGetInt_2490f0((s32)arg0);
        MenuWinSetColorInt_26c330(h, a, b, c, 0);
        MenuWinFadeColorToInt_26c1c0(h, a, b, c, 0x80, id);
        break;
    }
    return 1;
}
