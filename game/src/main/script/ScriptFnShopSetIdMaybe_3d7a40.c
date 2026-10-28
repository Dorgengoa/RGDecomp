/* rgp:protos */
#define RGP_SELF_ScriptFnShopSetIdMaybe_3d7a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} Obj00483960;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Obj00483960 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnShopSetIdMaybe_3d7a40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    ShopParamSetShopIdMaybe_3e8460(D_00483960, (s16)((short)VariantGetS16_36fcc0(arg3)));
        StateVarSet_3cc9c0(D_00483960->unk10, 0x79, 1, 1);
        VariantSetS32_36f040(arg0, 1, 1);
}
