/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityPageRefreshState_342350 1
#define RGP_SELF_calc 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    u8 pad8[0x1A - 8];
    s16 unk1A;
} ElemD48364;

typedef struct {
    u8 pad0[0x6C];
    s8 unk6C;
    u8 pad6d[0x70 - 0x6D];
    f32 unk70;
    s16 unk74;
} Ctx00482378;

/*rgp*/ /* extern */
/*rgp*/                 /* extern */
/*rgp*/                   /* extern */
/*rgp*/         /* extern */
/*rgp*/              /* extern */
/*rgp*/          /* extern */
/*rgp*/              /* extern */
extern f32 D_0047D65C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Ctx00482378 *D_00482378;

static inline f32 calc(f32 x,f32 k){return (f32)x*k+48.0f;}
s32 MenuCharaAbilityPageRefreshState_342350(s32 arg0, s32 arg1) {
    ElemD48364 *temp_2;
    ElemD48364 *temp_19;

    if (arg1 != 0) {
        temp_2 = ((ElemD48364 *)UiEntryListFindByTag_28ea40(D_00482364, 0x18));
        UiSetWidgetPos_290f60(D_00482360, 0x19E, temp_2->unk4, temp_2->unk6);
        UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 1.0f, D_0047D65C, -1.0f);
        temp_19 = ((ElemD48364 *)UiEntryListFindByTag_28ea40(D_00482364, 0x19));
        MenuCharaAbilityPageFill_3406a0(D_00482378, D_00482378->unk6C, temp_19->unk1A);
        D_00482378->unk70 = UiPageScrollBarLayout_289710(D_00482378, 0x19A, 0xA8, 6, D_00482378->unk74, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x19A, 0x180,
                     (s32) (calc(temp_19->unk1A,D_00482378->unk70)));
        MenuPartyIconsMarkLearnableMaybe_340de0(D_00482378, 0x19C);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x71, 0);
    return 1;
}
