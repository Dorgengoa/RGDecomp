/* rgp:protos */
#define RGP_SELF_ScriptFnMapApplySaveStateMaybe_3d6c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

/*rgp*/
/*rgp*/

void ScriptFnMapApplySaveStateMaybe_3d6c70(void *a0)
{
    if (a0 == 0) {
        return;
    }
    VariantSetS32_36f040(a0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    MapApplySaveStateMaybe_1fe560();
    VariantSetS32_36f040(a0, 1, 1);
}
