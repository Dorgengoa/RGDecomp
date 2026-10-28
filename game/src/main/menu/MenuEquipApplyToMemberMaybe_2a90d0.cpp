/* rgp:protos */
#line 1
#include "types.h"

typedef struct Card Card;

class Member {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 getName() { return VCM0(s32, 0x60); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void attach(Card *c) { VCM(void, (void *, Card *), 0x3DC, c); }
};

typedef struct Cursor {
    u8 pad[0x14];
    s16 col;
    s16 row;
} Cursor;

typedef struct Face {
    u8 pad[0x2C];
    s16 x2C;
} Face;

struct Card {
    u8 pad[0x10];
    Face *face;
};

typedef struct Panel {
    s16 x;
    s16 y;
} Panel;

typedef struct Party {
    u8 pad[0x18];
    s32 x18;
} Party;

typedef struct Menu {
    u8 pad[0x11];
    s8 x11;
} Menu;

extern "C" {
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu *D_00482374;
extern s8 D_00482500;
extern f32 D_0047D6E4;
extern f32 D_0047D35C;
extern f32 D_0047D588;
extern f32 D_0047D6E8;
extern f32 D_0047D6D0;
extern u8 D_004B2570[];

extern Cursor *UiEntryListFindByTag_28ea40(s32 a, s32 b);
extern void UiEntryListSelectByTag_28ea90(s32 a, s32 b, s32 c);
extern void UiFadeWidgetAlpha_290690(s32 a, s32 b, f32 x, f32 y, f32 z);
extern Party *GetGameData_1fede0(void);
extern Card *MenuGetItemAtCell_2a7000(s32 a, s32 b);
extern Panel *UiGetWidgetSprite_28fe10(s32 a, s32 b, s32 c);
extern void UiSetItemIconUv_288e50(Panel *p, s32 a, s32 b, s32 c);
extern void UiSetSpriteFlags_290bd0(s32, s32, long long, s32, s32, s32);
extern void UiSetWidgetColor_2905b0(s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void UiFadeWidgetColor_2904e0(s32 a, s32 b, f32 x, f32 y, f32 z, f32 w, f32 v);
extern Member *PartyGetSlotChara_3c2fb0(s32 a, s32 b);
extern void MenuSetTitleFmtMaybe_2a3f40(Menu *m, s32 n);
extern void PlayMenuSe_289ef0(s32 a);
extern f32 *UiGetWidgetColor_2904b0(s32 a, s32 b);
extern void UiSetWidgetsVisibleById_291110(s32 a, s32 b, s32 c, s32 d);
extern void UiSetWidgetPos_290f60(s32 a, s32 b, s32 c, s32 d);
extern s32 MenuGridCursorInput_28e170(s32 a, void *b, s32 c, s32 d);
extern void StateMachineSetState_28ede0(s32 a, s32 b, s32 c);
}

extern "C" s32 MenuEquipApplyToMemberMaybe_2a90d0(s32 unused, s32 init)
{
    Cursor *cur;
    s32 sel;
    Party *party;
    Card *card;
    Panel *panel;
    s32 i;
    Member *m;
    s32 r;
    s32 t;

    cur = UiEntryListFindByTag_28ea40(D_00482364, 10);
    sel = cur->col + cur->row * 4;
    if (init) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D6E4, -1.0f);
        party = GetGameData_1fede0();
        t = (s32)UiEntryListFindByTag_28ea40(D_00482364, 3);
        card = MenuGetItemAtCell_2a7000(D_00482374->x11, t + 4);
        if (card == 0) {
            return 0;
        }
        panel = UiGetWidgetSprite_28fe10(D_00482360, 0xB0, sel);
        if (panel == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(panel, card->face->x2C, 0x28, 0x2D);
        panel->x = cur->col * 97 + 0x4E;
        panel->y = (cur->row + 1) * 97;
        for (i = 0; i < 8; i++) {
            if (i == sel) {
                UiSetSpriteFlags_290bd0(D_00482360, 0xB0, (long long)(8), -1, i, 0);
            } else {
                UiSetSpriteFlags_290bd0(D_00482360, 0xB0, (long long)(8), 1, i, 0);
            }
        }
        UiSetWidgetColor_2905b0(D_00482360, 0xB0, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f);
        UiFadeWidgetColor_2904e0(D_00482360, 0xB0, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D588);
        m = PartyGetSlotChara_3c2fb0(party->x18, sel);
        if (m == 0) {
            return 0;
        }
        MenuSetTitleFmtMaybe_2a3f40(D_00482374, m->getName());
        m->attach(card);
        PlayMenuSe_289ef0(9);
        D_00482500 = 0;
    }
    if (*UiGetWidgetColor_2904b0(D_00482360, 0xB0) < D_0047D6E8 && D_00482500 == 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0xB4, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0xB4, 0x89, 0xD2);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB4, 1.0f, D_0047D6D0, 0.0f);
        D_00482500 = 1;
    }
    if (D_00482500 == 1) {
        r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        if (r == 1 || r == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x48, 0);
        }
    }
    return 1;
}
