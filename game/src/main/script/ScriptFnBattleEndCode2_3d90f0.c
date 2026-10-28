/* rgp:protos */
#define RGP_SELF_ScriptFnBattleEndCode2_3d90f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00483960;
extern s32 D_00483964;
/*rgp*/
/*rgp*/

void ScriptFnBattleEndCode2_3d90f0(s32 arg0)
{
    if (arg0 != 0) {
        VariantSetS32_36f040(arg0, 0, 1);
        if (D_00483960 == 0 || D_00483964 == 0) {
            return;
        }
        GameDataBattleEnd_3e67c0(D_00483960, 2, 0, 1, 0);
    }
}
