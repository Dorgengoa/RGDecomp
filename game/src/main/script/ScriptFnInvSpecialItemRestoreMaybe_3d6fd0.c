/* rgp:protos */
#define RGP_SELF_ScriptFnInvSpecialItemRestoreMaybe_3d6fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnInvSpecialItemRestoreMaybe_3d6fd0(s32 arg0) {
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    InvSpecialItemRestoreMaybe_3e4250(D_00483960);
    VariantSetS32_36f040(arg0, 1, 1);
}
