/* rgp:protos */
#define RGP_SELF_EvCmdStreamPlayMwv_240420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdStreamPlayMwv_240420(s64 *arg0, s32 arg1)
{
    s32 h;
    f32 f;
    f32 v;
    f32 g;
    s32 r;

    if ((arg1 <= 0) && (arg1 > 3)) {
        return 0;
    }
    h = ScriptGetInt_2490f0((s32)arg0++);
    f = 1.0f;
    if (arg1 >= 2) {
        f = TaggedGetFloat_2490d0((s32)arg0++);
        if (f > 1.0f) {
            f = 1.0f;
        } else if (f < 0.0f) {
            f = 0.0f;
        }
    }
    r = 0;
    if (arg1 == 3) {
        r = ScriptGetInt_2490f0((s32)arg0);
    }
    StreamPlayMwv_207340(h, r != 0, f);
    return 1;
}
