/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct { s16 x, y; } Pos;
typedef struct { u8 f0; u8 lo : 1; u8 kind : 4; u8 hi : 3; u8 pad2[2]; } Cell;
typedef struct { s16 f0; u8 pad2[0xA]; s32 fC; s32 f10; u8 pad14[0x18]; s16 f2C; } Item;
typedef struct { u8 pad0[4]; s32 f4; } Tgt;
typedef struct { u8 pad0[0x20]; s32 f20; u8 pad24[4]; Tgt *f28; } Wnd;
typedef struct {
    u8 pad0[0x10];
    Pos pos;
    u8 pad14[8];
    Cell cells[1];
} Menu0;
typedef struct {
    u8 pad0[0x10];
    Pos pos;
    u8 pad14[0x76C - 0x14];
    s16 f76C;
    s16 f76E;
    u8 pad770[0x10];
    Pos saved[8];
} Menu;
class Finder {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * Find(s32 a0) { return VCM(Item *, (void *, s32), 0x70, a0); }
};
typedef struct { u8 pad0[8]; Finder *f8; } Q40;
typedef struct { u8 pad0[0x40]; Q40 *f40; } Q8;
typedef struct { u8 pad0[0x26]; s16 f26; } QC;
typedef struct { u8 pad0[8]; Q8 *f8; QC *fC; u8 pad10[8]; s32 f18; } Game;

extern "C" {
Game *GetGameData_1fede0(void);
void RevelationBoardSetCharaId_349880(Menu *, s32);
void RevelationBoardFadeInOut_34cf70(Menu *, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
void RevelationBoardIconPlaceMaybe_34cc90(Menu *);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void UiGetWidgetTargetPos_290d90(s32, s32, s32 *, s32 *);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
s32 RevelationBoardLatchComplete_34c7c0(Menu *);
s32 GetLoaderMgr_1f59d0(void);
void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
void RevelationBoardDrawCellInfoMaybe_348d60(void);
f32 UiGetWidgetAlpha_290770(s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void RevelationBoardUpdate_34c290(Menu *);
s32 RevelationBoardCursorUpdateMaybe_34d080(Menu *, s32, s32, s32);
Cell * RevelationBoardGetCells_3eb510(Game *, s32, int, int);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
Item * RevelationBoardCellGetItemRec_3ead00(Game *, s32, Cell *, int);
Wnd *UiFindWidget_290460(s32, s32);
void UiSetItemIconUv_288e50(s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
s32 PadIsTriggered_1839f0(void *, s32);
void RevelationBoardBeginCloseMaybe_34c7a0(Menu *);
s32 RevelationBoardIsIdle_34c780(Menu *);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
s32 InvCountById_3c78d0(s32, s32, s32, s32);
void PartyMenuCursorSet_3c0710(s32, s32, s32);
void MenuGridGetCursor_34d060(Menu *, s32 *, s32 *);
void MenuRevelationBoardSwitchMember_348a40(void);
extern f32 D_0047D5D0;
extern f32 D_0047D638;
extern s32 D_0047F6C0;
extern s32 D_0047F6C4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu *D_0048238C;
extern Cell *D_00482E18;
extern Cell *D_00482E1C;
extern s16 D_00482E20;
extern s16 D_00482E24;
extern s16 D_00482E28;
extern s32 D_00482E34;
extern u8 D_004B2570[];

s32 MenuRevelationBoardState_347dd0(s32 arg0, s32 first) {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 cx;
    s32 cy;
    s32 ax;
    s32 ay;
    s32 dx;
    s32 dy;
    bool done;
    Game *g;
    Menu *mm;
    Pos *pos;
    Pos *p2;
    Cell *base;
    Cell *cell;
    Cell *cells;
    Item *it;
    Wnd *w;
    Tgt *tg;
    s32 st;
    u8 k;
    s32 id;
    s32 r;

    done = 0;
    g = GetGameData_1fede0();
    if (g == 0) {
        return 1;
    }
    if (first != 0) {
        RevelationBoardSetCharaId_349880(D_0048238C, D_0047F6C4);
        RevelationBoardFadeInOut_34cf70(D_0048238C, 1);
        if (D_00482E20 == 0) {
            D_00482E28 = 1;
        }
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1A, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x50, 0, 0, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x49, 0, 0, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x4B, 0xC, 0x153, D_0047D5D0, 0);
        if (D_00482E20 != 0) {
            RevelationBoardIconPlaceMaybe_34cc90(D_0048238C);
        }
    }
    if (D_00482E24 != 0) {
        UiGetWidgetPos_2910a0(D_00482360, 0x47, &x0, &y0);
        UiGetWidgetTargetPos_290d90(D_00482360, 0x47, &x1, &y1);
        if (x0 == x1 && y0 == y1) {
            UiFadeWidgetAlpha_290690(D_00482360, 0x52, 0.0f, D_0047D5D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x51, 0.0f, D_0047D5D0, -1.0f);
            UiMoveWidgetUniform_290f50(D_00482360, 0x52, 0x15A, 0x188, D_0047D5D0, 0);
            UiMoveWidgetUniform_290f50(D_00482360, 0x51, 0x15D, 0x18B, D_0047D5D0, 0);
            UiSetWidgetsVisibleById_291110(D_00482360, 0xB5, 0, 1);
            if (D_00482E24 == 1) {
                StateMachineSetState_28ede0(D_0048235C, 0x73, 0);
            } else if (D_00482E24 == 2) {
                StateMachineSetState_28ede0(D_0048235C, 0x76, 0);
            }
            D_00482E24 = 0;
        }
        return 0;
    }
    if (((short)RevelationBoardLatchComplete_34c7c0(D_0048238C)) != 0) {
        StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 0.0f);
        RevelationBoardDrawCellInfoMaybe_348d60();
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0x187) <= 0.0f) {
        UiSetWidgetVisible_290010(D_00482360, 0x187, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 1, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0xB, 0, -1);
    }
    pos = &D_0048238C->pos;
    RevelationBoardUpdate_34c290(D_0048238C);
    D_00482E18 = 0;
    D_00482E1C = 0;
    st = D_0048238C->f76E;
    if (((st == 0 || st == 9) && RevelationBoardCursorUpdateMaybe_34d080(D_0048238C, D_0047F6C0, D_0047F6C4, 0) != 0) || first != 0 || D_0048238C->f76C == -1) {
        p2 = &D_0048238C->pos;
        base = RevelationBoardGetCells_3eb510(g, D_0047F6C4, 0, 0);
        cell = &base[p2->x + p2->y * 26];
        D_00482E18 = cell;
        cells = ((Menu0 *)D_0048238C)->cells;
        if (cells != 0) {
            D_00482E1C = &cells[p2->x + p2->y * 26];
        }
        if (cell == 0) {
            goto next;
        }
        k = cell->kind;
        switch (k) {
        case 14:
        case 13:
        case 12:
        case 11:
            k = base[pos->x + pos->y * 26].kind;
            if (k == 11 || k == 12 || k == 13 || k == 14) {
                UiSetWidgetPos_290f60(D_00482360, 0x52, 0x10E, 0x188);
                UiSetWidgetPos_290f60(D_00482360, 0x51, 0x111, 0x18B);
            } else {
                UiSetWidgetPos_290f60(D_00482360, 0x52, 0x15A, 0x188);
                UiSetWidgetPos_290f60(D_00482360, 0x51, 0x15D, 0x18B);
            }
            st = D_0048238C->f76E;
            if (st == 0 || st == 9) {
                UiFadeWidgetAlpha_290690(D_00482360, 0x52, 1.0f, D_0047D5D0, -1.0f);
                UiFadeWidgetAlpha_290690(D_00482360, 0x51, D_0047D638, D_0047D5D0, -1.0f);
                D_00482E28 = 1;
                k = cell->kind;
                if (k == 11 || k == 12) {
                    UiFadeWidgetAlpha_290690(D_00482360, 0x5A, 1.0f, D_0047D5D0, -1.0f);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x5C, 1.0f, D_0047D5D0, -1.0f);
                    it = RevelationBoardCellGetItemRec_3ead00(g, D_0047F6C4, cell, 0);
                    if (it != 0) {
                        w = UiFindWidget_290460(D_00482360, 0x5B);
                        if (w == 0) {
                            return 0;
                        }
                        if (w->f20 != 0) {
                            UiSetItemIconUv_288e50(w->f20, it->f2C, 0x20, 0x24);
                        }
                        if (cell->kind == 11) {
                            UiSetWidgetColor_2905b0(D_00482360, 0x5B, D_0047D638, D_0047D638, D_0047D638, -1.0f);
                        } else {
                            UiSetWidgetColor_2905b0(D_00482360, 0x5B, 1.0f, 1.0f, 1.0f, -1.0f);
                        }
                    }
                } else {
                    UiFadeWidgetAlpha_290690(D_00482360, 0x5A, 0.0f, D_0047D5D0, -1.0f);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x5C, 0.0f, D_0047D5D0, -1.0f);
                }
            }
            UiMoveWidgetUniform_290f50(D_00482360, 0x52, 0x10E, 0x188, 0.25f, 0);
            UiMoveWidgetUniform_290f50(D_00482360, 0x51, 0x111, 0x18B, 0.25f, 0);
            w = UiFindWidget_290460(D_00482360, 0x52);
            if (w != 0) {
                tg = w->f28;
                it = RevelationBoardCellGetItemRec_3ead00(g, D_0047F6C4, cell, 0);
                if (tg != 0 && it != 0) {
                    k = cell->kind;
                    if (k == 11 || k == 12) {
                        tg->f4 = it->f10;
                    } else {
                        tg->f4 = it->fC;
                    }
                }
            }
            break;
        default:
            UiFadeWidgetAlpha_290690(D_00482360, 0x52, 0.0f, D_0047D5D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x51, 0.0f, D_0047D5D0, -1.0f);
            UiMoveWidgetUniform_290f50(D_00482360, 0x52, 0x15A, 0x188, D_0047D5D0, 0);
            UiMoveWidgetUniform_290f50(D_00482360, 0x51, 0x15D, 0x18B, D_0047D5D0, 0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x5A, 0.0f, D_0047D5D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x5C, 0.0f, D_0047D5D0, -1.0f);
            break;
        }
    }
next:
    if (D_0048238C->f76E == 6) {
        if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 || PadIsTriggered_1839f0(D_004B2570, 0x20) != 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x54, 0, 1);
            D_00482E28 = 1;
            D_00482E20 = 0;
            RevelationBoardBeginCloseMaybe_34c7a0(D_0048238C);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 && ((unsigned char)RevelationBoardIsIdle_34c780(D_0048238C)) != 0) {
        p2 = &D_0048238C->pos;
        base = RevelationBoardGetCells_3eb510(g, D_0047F6C4, 0, 0);
        cell = &base[p2->x + p2->y * 26];
        D_00482E20 = 0;
        if (cell != 0) {
            k = cell->kind;
            if (k == 11 || k == 12) {
                SoundPlayScaledVolume_1b9520(D_00482E34, 5, 0, 1.0f);
                done = 1;
                it = RevelationBoardCellGetItemRec_3ead00(g, D_0047F6C4, cell, 0);
                id = it->f0;
                if (id == 0x40F2 || id == 0x410B) {
                    if (InvHasItemInCategory_3c7f40(g->f18, 0x40F2, 0, 0) != 0) {
                        r = InvCountById_3c78d0(g->f18, it->f0, 0, 0);
                        D_00482E24 = 2;
                        if (r != 0) {
                            D_00482E24 = 1;
                        }
                    } else if (InvHasItemInCategory_3c7f40(g->f18, 0x410B, 0, 0) != 0) {
                        r = InvCountById_3c78d0(g->f18, g->f8->f40->f8->Find(0x410B)->f0, 0, 0);
                        D_00482E24 = 2;
                        if (r != 0) {
                            D_00482E24 = 1;
                        }
                    }
                } else {
                    r = InvCountById_3c78d0(g->f18, id, 0, 0);
                    D_00482E24 = 2;
                    if (r != 0) {
                        D_00482E24 = 1;
                    }
                }
            }
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x20) != 0 && ((unsigned char)RevelationBoardIsIdle_34c780(D_0048238C)) != 0) {
        SoundPlayScaledVolume_1b9520(D_00482E34, 6, 0, 1.0f);
        done = 1;
        UiFadeWidgetAlpha_290690(D_00482360, 0x52, 0.0f, D_0047D5D0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x51, 0.0f, D_0047D5D0, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x52, 0x15A, 0x188, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x51, 0x15D, 0x18B, D_0047D5D0, 0);
        mm = D_0048238C;
        {
            s32 i_ = D_0047F6C0;
            s16 y_ = mm->pos.y;
            s16 x_ = mm->pos.x;
            mm->saved[i_].x = x_;
            mm->saved[i_].y = y_;
        }
        p2 = &mm->pos;
        if (g->fC->f26 == 1) {
            {
                s16 v_ = 0;
                v_ |= p2->x;
                v_ |= p2->y << 8;
                PartyMenuCursorSet_3c0710(g->f18, D_0047F6C0 + 7, v_);
            }
        }
        StateMachineSetState_28ede0(D_0048235C, 0x8B, 0);
    }
    st = D_0048238C->f76E;
    if (st == 0 || st == 9) {
    UiGetWidgetPos_2910a0(D_00482360, 0x47, &cx, &cy);
    ax = 0;
    ay = 0;
    MenuGridGetCursor_34d060(D_0048238C, &ax, &ay);
    if (ax < 0xA0) {
        cx += 0xA0 - ax;
    } else if (ax > 0x160) {
        cx -= ax - 0x160;
    }
    if (ay < 0xA0) {
        cy += 0xA0 - ay;
    } else if (ay > 0x120) {
        cy -= ay - 0x120;
    }
    if (cx < -0x222) {
        cx = -0x222;
    } else if (cx > 0) {
        cx = 0;
    }
    if (cy < -0x1C0) {
        cy = -0x1C0;
    } else if (cy > 0x50) {
        cy = 0x50;
    }
    UiMoveWidgetUniform_290f50(D_00482360, 0x47, cx, cy, D_0047D5D0, 0);
    UiGetWidgetTargetPos_290d90(D_00482360, 0x47, &dx, &dy);
    if (!done) {
        MenuRevelationBoardSwitchMember_348a40();
    }
    }
    return 1;
}
}
