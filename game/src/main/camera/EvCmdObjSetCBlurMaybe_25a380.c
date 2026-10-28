/* rgp:protos */
#define RGP_SELF_EvCmdObjSetCBlurMaybe_25a380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjSetCBlurMaybe_25a380(s64 *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 v;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetInt_26a2a0((s32)arg0++);
    v = 1;
    if (arg1 >= 3) {
        v = (s32)TaggedGetFloat_26a280((s32)arg0);
    }
    GameSceneObjSetCBlurMaybe_1cf900(GetCurrentScene_1f5be0(), a, (f32)v, b);
    return 1;
}
