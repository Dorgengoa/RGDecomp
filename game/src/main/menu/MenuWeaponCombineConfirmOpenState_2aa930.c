/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineConfirmOpenState_2aa930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S2aa930 {
    u8 pad00[0x74];
    s16 m74;
} S2aa930;

typedef struct R2aa930 {
    u8 pad00[4];
    s16 m04;
    s16 m06;
    s16 m08;
    u8 pad0A[0xA];
    s16 m14;
} R2aa930;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_00482374;
extern void *D_004823D8;
extern void *D_00481BBC;
extern void *D_0048235C;
extern S2aa930 *D_00482384;
extern f32 D_0047D728;
extern f32 D_0047D6D0;
extern u8 D_004DB430[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuWeaponCombineConfirmOpenState_2aa930(s32 unused, s32 en)
{
    u8 v[0x10] __attribute__((aligned(16)));
    R2aa930 *r;
    S2aa930 *o;

    if (en != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0xD, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D728, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 0.0f, D_0047D728, -1.0f);
        MenuItemInfoWidgetsCache_2a65f0(v);
        MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, v, 0x68, 0x15E, -1, 2.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x13C, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x13C, 0xB2, 0x96);
        UiFadeWidgetAlpha_290690(D_00482360, 0x13C, 1.0f, D_0047D6D0, 0.0f);
        if (D_00482384->m74 == 0) {
            UiSetTextString_28f510(D_00482360, 0x13E, MsgTableLookup_28aa30(D_004823D8, 0x40B), 0);
        } else {
            UiSetTextString_28f510(D_00482360, 0x13E, MsgTableLookup_28aa30(D_004823D8, 0x40C), 0);
        }
        UiSetSpriteU_28f930(D_00482360, 0x13E, 0x4C, 0);
        UiSetSpriteU_28f930(D_00482360, 0x13E, 0x18, 1);
        UiSetTextString_28f510(D_00482360, 0x13E, MsgTableLookup_28aa30(D_00481BBC, 0x52), 1);
        UiSetTextString_28f510(D_00482360, 0x13E, MsgTableLookup_28aa30(D_00481BBC, 0x53), 2);
        r = ((R2aa930 *)UiEntryListFindByTag_28ea40(D_00482364, 0xD));
        r->m14 = 0;
        UiSetWidgetPos_290f60(D_00482360, 0x13F, r->m04 + r->m14 * r->m08, r->m06);
    }
    o = D_00482384;
    MenuWeaponCombineAutoHideTick_362700(o);
    MenuWeaponCombineAnimTickMaybe_361cd0(o);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    StateMachineSetState_28ede0(D_0048235C, 0x27, 0);
    return 1;
}
