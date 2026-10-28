/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on


class Lst {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

struct Mgr {
    u8 pad0[0xC];
    Lst *a;
    Lst *b;
};

struct Sys2 {
    u8 pad0[0x8C];
    Mgr *mgr;
};

struct Sys1 {
    u8 pad0[0x14];
    s32 f14;
};

struct Cell {
    u8 b0;
    u8 lo : 1;
    u8 type : 4;
    u8 hi : 3;
    u8 b2;
    u8 b3;
};

struct Map {
    Cell cells[1];
};

struct Pos {
    u8 pad0[0x16];
    s16 v;
};

struct Hit {
    struct Item *item;
    u8 pad4[0x12];
    s16 v;
};

struct Item {
    u8 pad0[8];
    s32 name;
};

struct Rc {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 uw;
    s16 vh;
    u8 pad10[0x10];
};

struct Lbl {
    u8 pad0[4];
    s32 name;
    u8 pad8[4];
    u32 col;
};

struct Wnd {
    u8 pad0[0x20];
    Rc *rc;
    u8 pad24[4];
    Lbl *lbl;
};

struct Win {
    s32 h;
    s32 f4;
    u8 pad8[8];
    s16 x;
    s16 y;
    u8 pad14[0x774 - 0x14];
    f32 f774;
    u8 pad778[0x7A2 - 0x778];
    u8 f7A2;
};

extern "C" {
Sys1 *GetGameData_1fede0(void);
Sys2 *GetWorldDataMgr_1fedf0(void);
Map * RevelationBoardGetCells_3eb510(Sys1 *, s32, int, int);
s32 CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
void RevelationBoardCellGetValue_3eade0(Sys1 *, s32, s32, int);
Hit * RevelationBoardCellGetEntry_3eae10(Sys1 *, s32, Cell *, int);
Wnd *UiFindWidget_290460(s32, s32);
void FontMeasureString_26daf0(void *, s32, s32 *, s32 *);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
f32 Sinf_128fd0(f32);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
}
extern "C" f32 D_0047D488;
extern "C" f32 D_0047D49C;
extern "C" u8 D_004DB150[];

extern "C" void RevelationBoardDrawItemBalloonMaybe_349920(Win *w, s32 id) {
    Sys1 *s1;
    Sys2 *s2;
    Map *map;
    Cell *cell;
    Hit *hit;
    Item *item;
    s32 row;
    s32 col;
    Wnd *wnd;
    Rc *rc;
    Lbl *lbl;
    s32 bx;
    s32 by;
    s32 x;
    s32 w01;
    s32 y;
    s32 right;
    s32 tw;
    s32 th;
    s32 o[2];
    bool flag;

    s1 = GetGameData_1fede0();
    if (s1 == 0) {
        return;
    }
    s2 = GetWorldDataMgr_1fedf0();
    if (s2 == 0) {
        return;
    }
    map = RevelationBoardGetCells_3eb510(s1, id, 0, 0);
    if (map == 0) {
        return;
    }
    s2->mgr->a->v26(id);
    if (CharaMgrPoolFindByDataId_3a8a70(s1->f14, id, 1, 1, 0, 0, 0) == 0) {
        return;
    }
    if (s2->mgr->b->v26(id) == 0) {
        return;
    }
    if (w->f4 != 0) {
        RevelationBoardCellGetValue_3eade0(s1, id, w->f4, 0);
    }
    cell = &map->cells[w->x + w->y * 26];
    flag = 0;
    if (cell->type >= 11) {
        hit = RevelationBoardCellGetEntry_3eae10(s1, id, cell, 0);
        if (hit != 0) {
            item = hit->item;
            if (item != 0) {
                row = hit->v / 26;
                col = hit->v % 26;
                wnd = UiFindWidget_290460(w->h, 0x53);
                if (wnd != 0) {
                    rc = wnd->rc;
                    if (rc != 0 && D_004DB150 != 0) {
                        FontMeasureString_26daf0(D_004DB150, item->name, &tw, &th);
                        bx = col * 42 + 40;
                        by = row * 46 - 50;
                        rc[2].x = tw / 2 - 6;
                        rc[1].w = rc[3].w = tw / 2;
                        rc[1].x = rc[2].x - rc[1].w;
                        rc[3].x = rc[2].x + rc[2].w;
                        rc[0].x = rc[2].x - rc[1].w - rc[0].w;
                        rc[4].x = rc[3].x + rc[3].w;
                        lbl = wnd->lbl;
                        w01 = rc[0].w + rc[1].w;
                        if (lbl != 0) {
                            lbl->name = item->name;
                            if (cell->type == 14) {
                                rc[0].u = 0x18; rc[0].v = 0x5E; rc[0].uw = 0x10; rc[0].vh = 0x22;
                                rc[1].u = 0x28; rc[1].v = 0x5E; rc[1].uw = 0x8; rc[1].vh = 0x22;
                                rc[2].u = 0x52; rc[2].v = 0xA2; rc[2].uw = 0xC; rc[2].vh = 0x30;
                                rc[3].u = 0x28; rc[3].v = 0x5E; rc[3].uw = 0x8; rc[3].vh = 0x22;
                                rc[4].u = 0x2E; rc[4].v = 0x5E; rc[4].uw = 0x10; rc[4].vh = 0x22;
                                lbl->col = 0xFF303030;
                            } else {
                                rc[0].u = 0x18; rc[0].v = 0x2E; rc[0].uw = 0x10; rc[0].vh = 0x22;
                                rc[1].u = 0x28; rc[1].v = 0x2E; rc[1].uw = 0x8; rc[1].vh = 0x22;
                                rc[2].u = 0x30; rc[2].v = 0x2E; rc[2].uw = 0xC; rc[2].vh = 0x30;
                                rc[3].u = 0x28; rc[3].v = 0x2E; rc[3].uw = 0x8; rc[3].vh = 0x22;
                                rc[4].u = 0x3C; rc[4].v = 0x2E; rc[4].uw = 0x10; rc[4].vh = 0x22;
                                lbl->col = 0xFF202020;
                            }
                        }
                        UiSetWidgetsVisibleById_291110(w->h, 0x53, 1, 1);
                        x = bx - w01;
                        y = (f32)by + 6.0f * Sinf_128fd0(w->f774);
                        right = x + rc[0].w + rc[1].w + rc[2].w + rc[3].w + rc[4].w;
                        UiGetWidgetPos_2910a0(w->h, 0x47, &o[1], &o[0]);
                        o[0] = -o[0];
                        o[1] = -o[1];
                        if (y < o[0] + 30) {
                            y = o[0] + 30;
                        }
                        if (x < o[1] + 42) {
                            x = o[1] + 42;
                        } else if (o[1] + 518 < right) {
                            x = o[1] + 518 - (rc[0].w + rc[1].w + rc[2].w + rc[3].w + rc[4].w);
                        }
                        UiSetWidgetPos_290f60(w->h, 0x53, x, y);
                        if (w->f7A2 == 0) {
                            UiFadeWidgetAlpha_290690(w->h, 0x53, 1.0f, D_0047D488, -1.0f);
                        }
                        flag = 1;
                    }
                }
            }
        }
    }
    if (!flag && w->f7A2 == 0) {
        UiFadeWidgetAlpha_290690(w->h, 0x53, 0.0f, D_0047D49C, -1.0f);
    }
}
