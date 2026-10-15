#include "types.h"
extern "C" {

typedef struct {
    u8 pad0[0x94];
    s8 b94;
    s8 b95;
} R;

typedef struct {
    u8 pad0[0xE];
    s16 hE;
    u8 pad10[4];
    u16 h14;
    s16 h16;
} H;

typedef struct {
    u8 pad0[0x11];
    s8 b11;
    u8 pad12[0x30];
    s16 h42;
} G;

extern void GetGameData_1fede0(void);
extern H *UiEntryListFindByTag_28ea40(void *, s32);
extern void UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void MenuItemCmdColors_2a1140(G *, void *, s32);
extern void MenuItemCmdSetRowHighlight_2a1800(G *, s32, s32, s32, s32);
extern void MenuItemCmdPopupPlaceMaybe_2a4620(G *, s32, s32, s16, s16, s16, s16, s32);
extern s32 MenuItemCountPanelSetupMaybe_2a53f0(G *, void *, s32, s32, s32, s32, bool);
extern void MenuItemCmdFrameResize_2a5750(G *, s32, s16);
extern void MenuItemCmdLabelsSet_2a6060(G *, s16);
extern void *MenuGetItemAtCell_2a7000(s32, void *);
extern s32 ItemRecKindIs6_3d4510(void *);
extern s32 ItemKindBelow4_3d4860(void *);
extern s32 ItemDefIsKindCId4B1_40e2e0(void *);
extern s32 ItemDefIsKindCId4B0_40e310(void *);
extern const f32 D_0047D770 __attribute__((section(".sdata")));
extern void *D_0048235C;
extern void *D_00482360;
extern void *D_00482364;
extern G *D_00482374;
extern R *D_00482384;
extern u8 D_004823CC;

s32 MenuItemCommandOpenState_2b0a00(s32 arg0, s32 arg1)
{
        void * arg_h0;

    f32 t;
    H *h2;
    void *obj;
    s32 mode;
    s32 kind;
    R *r;
    H *h;
    s16 m16;
    void *sub;
    s16 k16;
    bool flag;

    if (arg1 != 0) {
        if (D_004823CC != 0) {
            r = D_00482384;
            r->b94 = r->b95;
            r->b95 = 3;
        }
        arg_h0 = D_00482364;
        UiEntryListSelectByTag_28ea90(arg_h0, 0x27, 0);
        GetGameData_1fede0();
        h = UiEntryListFindByTag_28ea40(D_00482364, 4);
        h->h16 = 0;
        h2 = UiEntryListFindByTag_28ea40(D_00482364, 3);
        obj = MenuGetItemAtCell_2a7000(D_00482374->b11, (u8 *)h2 + 4);
        if (obj == NULL) {
            return 0;
        }
        flag = true;
        if (D_004823CC != 0) {
            kind = 3;
            mode = 2;
            flag = false;
        } else if (ItemKindBelow4_3d4860(obj) != 0) {
            kind = 5;
            mode = 1;
        } else if (ItemRecKindIs6_3d4510(obj) != 0) {
            kind = 4;
            mode = 3;
        } else {
            sub = *(void **)((u8 *)obj + 0x10);
            kind = 6;
            mode = 0;
            if (ItemDefIsKindCId4B1_40e2e0(sub) != 0) {
                mode = 5;
            } else if (ItemDefIsKindCId4B0_40e310(sub) != 0) {
                mode = 4;
            }
        }
        k16 = kind;
        m16 = mode;
        h->hE = k16 - 1;
        MenuItemCmdFrameResize_2a5750(D_00482374, 0x7E, m16);
        MenuItemCmdPopupPlaceMaybe_2a4620(D_00482374, 0x7E, 0x7D, h2->h14, h2->h16, k16, m16, MenuItemCountPanelSetupMaybe_2a53f0(D_00482374, obj, 0x7F, 0x82, 0x80, 0x81, flag));
        MenuItemCmdLabelsSet_2a6060(D_00482374, m16);
        MenuItemCmdSetRowHighlight_2a1800(D_00482374, 0x7E, 0x7D, 0, mode);
        MenuItemCmdColors_2a1140(D_00482374, obj, mode);
        t = D_0047D770;
        D_00482374->h42 = mode;
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, t, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x1A7, 0, 0);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x12, 1);
    return 1;
}
}
