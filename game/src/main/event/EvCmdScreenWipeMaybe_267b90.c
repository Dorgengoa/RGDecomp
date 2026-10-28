/* rgp:protos */
#define RGP_SELF_EvCmdScreenWipeMaybe_267b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00481F78;

s32 EvCmdScreenWipeMaybe_267b90(E8 *p0, s32 p1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    ScreenFadeCaptureFrame_1cf550(D_00481F78);
    if (p1 == 3) {
        a = ScriptGetInt_26a2a0(p0++);
        b = ScriptGetInt_26a2a0(p0++);
        c = ScriptGetInt_26a2a0(p0);
        if (a == 0) {
            ScreenFadeWipeInMaybe_1cf710(D_00481F78, b, c, 1.0f);
        } else {
            ScreenFadeWipeOutMaybe_1cf700(D_00481F78, b, c, 1.0f);
        }
    } else {
        d = ScriptGetInt_26a2a0(p0);
        ScreenFadeDissolveIn_1cf720(D_00481F78, d, 1.0f);
    }
    return 1;
}
