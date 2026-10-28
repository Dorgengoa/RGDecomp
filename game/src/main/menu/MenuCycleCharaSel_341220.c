/* rgp:protos */
#define RGP_SELF_MenuCycleCharaSel_341220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x6C];
    s8 sel;
    u8 pad6D[3];
    f32 unk70;
    s16 unk74;
    s16 unk76;
} Menu00341220;

typedef struct {
    u8 pad0[0x14];
    s16 unk14;
    s16 unk16;
    u8 pad18[2];
    s16 unk1A;
} Win00341220;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Sys00341220;

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
/*rgp*/
/*rgp*/
extern f32 D_0047D34C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu00341220 *D_00482378;
extern u8 D_004B2570[0x400];

s32 MenuCycleCharaSel_341220(u8 *self, s32 arg1) {
    u8 *pad;
    s32 n;
    s32 sel;
    s32 changed;
    Win00341220 *w;
    Win00341220 *w2;

    pad = D_004B2570;
    n = ((Sys00341220 *)GetGameData_1fede0())->unk18;
    n = PartyCountMembers_3c2010(n, 1, 1) + PartyCountReserve_3c1c20(n, 1, 1);
    sel = D_00482378->sel;
    changed = 0;
    if (n >= 2) {
        if (PadIsTriggered_1839f0(pad, 0x8004) != 0) {
            if (sel > 0) {
                sel--;
                changed = 1;
            } else if (PadIsRepeatTriggered_183dd0(pad, 0x8004) == 0) {
                sel = n - 1;
                changed = 1;
            }
        } else if (PadIsTriggered_1839f0(pad, 0x2008) != 0) {
            if (sel < n - 1) {
                sel++;
                changed = 1;
            } else if (PadIsRepeatTriggered_183dd0(pad, 0x2008) == 0) {
                sel = 0;
                changed = 1;
            }
        }
    }
    if (changed) {
        if (PadIsTriggered_1839f0(pad, 0xA000) == 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        }
        *(s16 *)(self + 0x12) = 0;
        UiSetWidgetPos_290f60(D_00482360, 0x18D, 0, 0);
        MenuSetTabStyleMaybe_340a40(D_00482378, 0x19B, sel);
        D_00482378->sel = sel;
        MenuCharaAbilityPageFill_3406a0(D_00482378, sel, 0);
        MenuSetMemberValueTextMaybe_3405a0(D_00482378, sel);
        D_00482378->unk70 = UiPageScrollBarLayout_289710(D_00482378, 0x19A, 0xA8, 6, D_00482378->unk74, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x19A, 0x180, 0x30);
        D_00482378->unk76 = 0;
        w = ((Win00341220 *)UiEntryListFindByTag_28ea40(D_00482364, 0x19));
        w->unk1A = 0;
        w->unk16 = 0;
        MenuCharaAbilityPageSetRowRange_341ba0();
        w2 = ((Win00341220 *)UiEntryListFindByTag_28ea40(D_00482364, 0x17));
        w->unk14 = sel;
        w2->unk14 = sel;
        if (D_00482378->unk74 <= 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x18D, 0, 1);
            if (arg1 != 0) {
                StateMachineSetState_28ede0(D_0048235C, 0x6E, 0);
            } else {
                StateMachineSetState_28ede0(D_0048235C, 0x70, 0);
            }
            UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, -0x28, D_0047D34C, 0);
            UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, -0x25, D_0047D34C, 0);
        }
    }
    return 1;
}
