/* rgp:protos */
#define RGP_SELF_ScriptFnPendingWarpCancel_3d6720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern void *D_00483960;
extern s32 D_00483964;

void ScriptFnPendingWarpCancel_3d6720(s32 arg0)
{
    s32 temp_18;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    temp_18 = *(s32 *)((u8 *)D_00483960 + 0x18);
    PartyPendingWarpCancel_3c9830(temp_18);
    VariantSetS32_36f040(arg0, 1, 1);
}
