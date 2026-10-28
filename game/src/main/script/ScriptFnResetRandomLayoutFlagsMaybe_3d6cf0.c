/* rgp:protos */
#define RGP_SELF_ScriptFnResetRandomLayoutFlagsMaybe_3d6cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnResetRandomLayoutFlagsMaybe_3d6cf0(s32 arg0) {
    s32 var_17;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    RandomLayoutClear_1ff100();
    var_17 = 0x6A4;
    do {
        StateFlag2Set_3cc6d0(*(s32 *)((u8 *)D_00483960 + 0x10), var_17, 0);
        var_17 += 1;
    } while (var_17 < 0x800);
    VariantSetS32_36f040(arg0, 1, 1);
}
