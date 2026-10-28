/* rgp:protos */
#define RGP_SELF_ScriptFnBattleEndCode4_3d9080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00483960;
extern s32 D_00483964;

void ScriptFnBattleEndCode4_3d9080(s32 p0)
{
    s32 g;

    if (p0 != 0) {
        VariantSetS32_36f040(p0, 0, 1);
        g = D_00483960;
        if (g != 0) {
            if (D_00483964 != 0) goto ok;
        }
    }
    return;
ok:
    GameDataBattleBroadcastPhase_3e6890(g, 4);
    GameDataBattleEnd_3e67c0(D_00483960, 4, 0, 1, 0);
}
