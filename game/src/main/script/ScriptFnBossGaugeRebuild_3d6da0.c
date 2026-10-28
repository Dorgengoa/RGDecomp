/* rgp:protos */
#define RGP_SELF_ScriptFnBossGaugeRebuild_3d6da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

/*rgp*/
/*rgp*/

void ScriptFnBossGaugeRebuild_3d6da0(void *a0)
{
    if (a0 == 0) {
        return;
    }
    VariantSetS32_36f040(a0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    func_507170();
    VariantSetS32_36f040(a0, 1, 1);
}
