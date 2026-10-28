/* rgp:protos */
#define RGP_SELF_ScriptFnMapMarkerSetRemoveMaybe_3d77c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00483960 {
    u8 pad10[0x10];
    s32 unk10;
} S00483960;

/*rgp*/
/*rgp*/
/*rgp*/
extern S00483960 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnMapMarkerSetRemoveMaybe_3d77c0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_5;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    var_5 = -1;
    if (arg2 > 0) {
        var_5 = (s32) VariantGetFloat_36f7a0(arg3);
    }
    StateBlockMapMarkerSetRemoveMatchingMaybe_3cc050(D_00483960->unk10, var_5, 0, 0);
    VariantSetS32_36f040(arg0, 1, 1);
}
