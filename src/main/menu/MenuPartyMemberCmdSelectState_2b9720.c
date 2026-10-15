#include "types.h"

typedef struct R2b9720 {
    u8 pad0[0x18];
    s32 unk18;
} R2b9720;

typedef struct E2b9720 {
    s8 b0;
    s8 b1;
} E2b9720;

typedef struct T2b9720 {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    u8 pad8[0xA];
    s16 h12;
} T2b9720;

extern R2b9720 *GetGameData_1fede0(void);
extern E2b9720 *MenuGetCursorPos_29fae0(s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void MenuWidgetFadeInOut_29fb00(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetParent_2911a0(s32, s32, s32);
extern T2b9720 *UiEntryListFindByTag_28ea40(s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern void PartyGetSlotChara_3c2fb0(s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern T2b9720 *UiEntryListGetCurrentData_28ec60(s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 MenuPartyCmdRowIsDimmed_29c2f0(s32, s32, s16);
extern u16 D_004614C0[0x200];
extern f32 D_0047D6C8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern u8 D_004B2570[];

s32 MenuPartyMemberCmdSelectState_2b9720(s32 pad0, s32 arg1)
{
    R2b9720 *r;
    E2b9720 *e;
    u16 id;
    T2b9720 *t;
    s32 mode;
    s32 x;
    s32 y;

    r = GetGameData_1fede0();
    e = MenuGetCursorPos_29fae0(D_00482370);
    id = D_004614C0[e->b1];
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x11, 0);
        UiSetWidgetVisible_290010(D_00482360, id, 1, -1);
        MenuWidgetFadeInOut_29fb00(D_00482370, id, 1, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x183, 1.0f, D_0047D6C8, -1.0f);
        UiSetWidgetParent_2911a0(D_00482360, 0x183, id);
        UiSetWidgetParent_2911a0(D_00482360, 0x118, id);
        t = UiEntryListFindByTag_28ea40(D_00482364, 0x11);
        PartyGetSlotChara_3c2fb0(r->unk18, e->b0 + e->b1 * PartyCountMembers_3c2010(r->unk18, 1, 1));
        UiSetWidgetPos_290f60(D_00482360, 0x183, t->h4, t->h6);
    }
    mode = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 4, 0);
    t = UiEntryListGetCurrentData_28ec60(D_00482364);
    x = 0;
    y = 0;
    UiGetWidgetPos_2910a0(D_00482360, id, &x, &y);
    x += 0x42;
    y += 0x42;
    if (mode == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x50, 0);
    } else if (mode == 1) {
        PartyGetSlotChara_3c2fb0(r->unk18, e->b0 + e->b1 * PartyCountMembers_3c2010(r->unk18, 1, 1));
        if (MenuPartyCmdRowIsDimmed_29c2f0(D_00482370, id, t->h12) == 0) {
            switch (t->h12) {
            case 0:
                StateMachineSetState_28ede0(D_0048235C, 0x51, 0);
                break;
            case 1:
                if (e->b1 == 0) {
                    StateMachineSetState_28ede0(D_0048235C, 0x66, 0);
                } else {
                    StateMachineSetState_28ede0(D_0048235C, 0x57, 0);
                }
                break;
            case 2:
                if (e->b1 == 0) {
                    StateMachineSetState_28ede0(D_0048235C, 0x57, 0);
                } else {
                    StateMachineSetState_28ede0(D_0048235C, 0x6A, 0);
                }
                break;
            case 3:
                StateMachineSetState_28ede0(D_0048235C, 0x6A, 0);
                break;
            }
        }
    }
    return 1;
}
