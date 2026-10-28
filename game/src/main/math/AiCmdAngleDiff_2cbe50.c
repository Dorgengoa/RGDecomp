/* rgp:protos */
#define RGP_SELF_AiCmdAngleDiff_2cbe50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC;
extern f32 D_0047D320;

s32 AiCmdAngleDiff_2cbe50(s64 *arg0)
{
    f32 a;
    f32 b;
    f32 d;
    f32 r;

    a = WrapAngle_13c050(ScriptSlotGetFloat_2cc9a0((s32)arg0++));
    b = WrapAngle_13c050(ScriptSlotGetFloat_2cc9a0((s32)arg0++));
    d = b - a;
    d = (d < 0.0f) ? -d : d;
    if (d < D_0047D1FC) {
        r = b;
        r -= a;
    } else {
        r = D_0047D320 - d;
        if (a < b) {
            r *= -1.0f;
        }
    }
    ScriptSlotStoreFloatRef_2cc8e0((s32)arg0, r);
    return 1;
}
