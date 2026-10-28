/* rgp:protos */
#define RGP_SELF_EvCmdSceneSetTint_241760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern s32 *gEventContext;

s32 EvCmdSceneSetTint_241760(s64 *arg0, s32 arg1) {
    s32 ctx;
    s32 a;
    s32 b;

    ctx = *gEventContext;
    if (ScriptGetInt_2490f0((s32)arg0++) != 0) {
        if (arg1 == 1) {
            GameSceneSetTint_1ce940(ctx, 1, 0x80, 0x80, 0x80);
        } else {
            a = ScriptGetInt_2490f0((s32)arg0++);
            b = ScriptGetInt_2490f0((s32)arg0++);
            GameSceneSetTint_1ce940(ctx, 1, a, b, ScriptGetInt_2490f0((s32)arg0++));
        }
    } else {
        GameSceneSetTint_1ce940(ctx, 0, 0x80, 0x80, 0x80);
    }
    return 1;
}
