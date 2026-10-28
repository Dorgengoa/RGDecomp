/* rgp:protos */
#define RGP_SELF_EvCmdScreenFadeOut_2679c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;

s32 EvCmdScreenFadeOut_2679c0(s64 *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = ScriptGetInt_26a2a0(arg0++);
    switch (arg1) {
    case 1:
        ScreenFadeReset_1cf760(D_00481F78);
        ScreenFadeOutColor_1cf730(D_00481F78, a, 0.0f, 0.0f, 0.0f);
        break;
    case 4:
        b = ScriptGetInt_26a2a0(arg0++);
        c = ScriptGetInt_26a2a0(arg0++);
        d = ScriptGetInt_26a2a0(arg0);
        ScreenFadeReset_1cf760(D_00481F78);
        ScreenFadeOutColor_1cf730(D_00481F78, a, (f32)b, (f32)c, (f32)d);
        break;
    }
    return 1;
}
