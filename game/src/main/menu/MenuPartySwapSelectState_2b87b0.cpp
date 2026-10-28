/* rgp:protos */
#line 1
#include "types.h"

typedef struct Bits {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 5;
} Bits;

class Item {
public:
    VC_VPTR_MEMBER;     
         
         
       
    s32 Qty() { return VCM0(s32, 0x60); } /* 0x60 */
         
         
         
         
         
        
    s32 Left() { return VCM0(s32, 0xF0); } /* 0xF0 */
    u8 pad4[0xC - 0x4];
    s32 xC;
    u8 pad10[0x234 - 0x10];
    Bits x234;
};

typedef struct Info {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u8 pad10[0xC];
    s32 x1C;
    u8 pad20[0x90];
} Info;

typedef struct Pos2 {
    f32 x;
    f32 y;
} Pos2;

typedef struct St {
    u8 pad0[0x10];
    s16 x10;
    s16 x12;
} St;

typedef struct Obj20 {
    u8 pad0[0x20];
    s32 x20;
} Obj20;

typedef struct Sys18 {
    u8 pad0[0x42D0];
    u8 x42D0;
} Sys18;

typedef struct Sys20 {
    u8 pad0[0x24C];
    u8 x24C;
} Sys20;

typedef struct Gm {
    u8 pad0[0x18];
    Sys18 *x18;
    u8 pad1C[4];
    Sys20 *x20;
} Gm;

extern "C" {
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
s32 MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
St *UiEntryListGetCurrentData_28ec60(s32);
Gm *GetGameData_1fede0(void);
s32 PartyCountMembers_3c2010(Sys18 *, s32, s32);
void MenuGetSwapPair_29f970(s32, s32 *, s32 *);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
Obj20 *UiFindWidget_290460(s32, s32);
s32 GetMenuResGroup_206a40(void);
s32 ResGroupListFindValueById_42c3a0(s32, s32);
void MenuPartyPanelIconSizesResetMaybe_29ddf0(s32);
void MenuSetCursorPos_29faf0(s32, s32, s32);
void MenuLayoutPartyPanelMaybe_29cfb0(s32, s32, s32, s32);
void MenuLayoutPartyFramesMaybe_29cb70(s32, s32, s32, s32);
void MenuSetPartyEquipIcon_29ec60(s32, s32, s32, s32);
void MenuPartyCharaIconsLayoutMaybe_29ad30(s32, s32, s16);
void MenuShowCharaStats_29bb00(s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
Item *PartyGetSlotChara_3c2fb0(Sys18 *, s32);
void MsgFormatParamsCtor_28aa00(Info *);
s32 MenuGetOpenLeaderId_29acd0(void);
s32 CharaIsNearLeaderMaybe_1fb230(s32, s32);
char *MsgTableLookup_28aa30(s32, s32);
void MsgFormat_28a9a0(char *, char *, Info *, s32);
char *strcpy(char *, char *);
void MenuSetSwapDst_29fa60(s32, s32);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
void UiSetTextString_28f510(s32, s32, char *, s32);
void UiSelFrameAnimStep_28d820(u8 *, s32);
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s32 D_004823D8;
extern s16 D_00482554;
extern s32 D_00482558;
extern s16 D_0048255C;
extern f32 D_0047ED30;
extern f32 D_0047ED34;
extern f32 D_0047D6BC;
extern u8 D_004B2570[];
extern char D_004DB820[];
extern u8 D_004DB730[];
extern u8 D_004DB760[];
s32 MenuPartySwapSelectState_2b87b0(s32 a0, s32 init);
}

extern "C" s32 MenuPartySwapSelectState_2b87b0(s32 a0, s32 init)
{
    Pos2 pt __attribute__((aligned(16)));
    Info info __attribute__((aligned(16)));
    s32 r;
    St *st;
    Gm *gm;
    s32 cnt;
    s32 flag;
    s32 sel;
    s32 b;
    Obj20 *o;
    s32 w;
    s32 p0;
    s32 idx;
    bool ok;
    Item *A;
    Item *B;
    bool can;
    s32 id;
    s32 cur;

    if (init) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x12, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x11F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x120, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x184, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14B, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14C, 1, 1);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    st = UiEntryListGetCurrentData_28ec60(D_00482364);
    gm = GetGameData_1fede0();
    cnt = PartyCountMembers_3c2010(gm->x18, 1, 1);
    pt.x = D_0047ED30;
    pt.y = D_0047ED34;
    MenuGetSwapPair_29f970(D_00482370, (s32 *)&pt.x, (s32 *)&pt.y);
    sel = *(s32 *)&pt.x;
    flag = sel >= cnt;
    if (sel >= cnt) {
        sel -= cnt;
    }
    b = (u8)(st->x12 == flag && sel == 0);
    if (r == 2) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x184, 0.0f, D_0047D6BC, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14B, 0.0f, D_0047D6BC, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14C, 0.0f, D_0047D6BC, -1.0f);
        o = UiFindWidget_290460(D_00482360, 0xD7);
        if (o != 0) {
            w = GetMenuResGroup_206a40();
            o->x20 = ResGroupListFindValueById_42c3a0(w, 0x3A2);
            MenuPartyPanelIconSizesResetMaybe_29ddf0(D_00482370);
            o->x20 = ResGroupListFindValueById_42c3a0(w, flag + 0x3A2);
        }
        MenuSetCursorPos_29faf0(D_00482370, sel, flag);
        MenuLayoutPartyPanelMaybe_29cfb0(D_00482370, 0xD7, sel, flag);
        MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, sel, flag);
        p0 = *(s32 *)&pt.x;
        MenuSetPartyEquipIcon_29ec60(D_00482370, p0, 0x113, 0);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p0, 0x114, 1);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p0, 0x115, 2);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p0, 0x116, 3);
        MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, p0);
        MenuShowCharaStats_29bb00(D_00482370, p0);
        StateMachineSetState_28ede0(D_0048235C, 0x54, 0);
    } else if (r == 1) {
        idx = b + st->x10 + st->x12 * cnt;
        A = PartyGetSlotChara_3c2fb0(gm->x18, idx);
        B = PartyGetSlotChara_3c2fb0(gm->x18, *(s32 *)&pt.x);
        ok = true;
        MsgFormatParamsCtor_28aa00(&info);
        if (!(*(s32 *)&pt.x < cnt) && st->x12 == 0) {
            id = A->xC;
            cur = ((short)MenuGetOpenLeaderId_29acd0());
            can = true;
            if (!(gm->x20->x24C & 1)) {
                if (CharaIsNearLeaderMaybe_1fb230(id, cur) == 0) {
                    can = false;
                }
            }
            if (A->x234.b0) {
                info.x1C = A->Qty();
                MsgFormat_28a9a0(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7D1), &info, 1);
                ok = false;
            } else if (A->Left() <= 0) {
                info.x1C = A->Qty();
                MsgFormat_28a9a0(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7DF), &info, 1);
                ok = false;
            } else if (!can && !(gm->x18->x42D0 & 1)) {
                info.x1C = A->Qty();
                MsgFormat_28a9a0(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7E0), &info, 1);
                ok = false;
            }
        } else if (*(s32 *)&pt.x < cnt && st->x12 == 1) {
            id = B->xC;
            cur = ((short)MenuGetOpenLeaderId_29acd0());
            can = true;
            if (!(gm->x20->x24C & 1)) {
                if (CharaIsNearLeaderMaybe_1fb230(id, cur) == 0) {
                    can = false;
                }
            }
            if (A->x234.b2) {
                strcpy(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7D0));
                ok = false;
            } else if (B->x234.b0) {
                info.x1C = B->Qty();
                MsgFormat_28a9a0(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7D1), &info, 1);
                ok = false;
            } else if (B->Left() <= 0) {
                info.x1C = B->Qty();
                MsgFormat_28a9a0(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7DF), &info, 1);
                ok = false;
            } else if (!can && !(gm->x18->x42D0 & 1)) {
                info.x1C = B->Qty();
                MsgFormat_28a9a0(D_004DB820, MsgTableLookup_28aa30(D_004823D8, 0x7E0), &info, 1);
                ok = false;
            }
        }
        if (ok) {
            MenuSetSwapDst_29fa60(D_00482370, idx);
            StateMachineSetState_28ede0(D_0048235C, 0x55, 0);
            SoundPlayScaledVolume_1b9520(D_00482558, 10, 0, 1.0f);
        } else {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x184, 0, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x14B, 0, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x14C, 0, 1);
            UiSetTextString_28f510(D_00482360, 0x21E, D_004DB820, 0);
            D_00482554 = 0x53;
            D_0048255C = 0;
            StateMachineSetState_28ede0(D_0048235C, 0x4D, 0);
        }
    }
    UiSelFrameAnimStep_28d820(D_004DB730, 0x14B);
    UiSelFrameAnimStep_28d820(D_004DB760, 0x14C);
    return 1;
}
