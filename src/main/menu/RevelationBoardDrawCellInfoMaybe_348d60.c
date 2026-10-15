#include "types.h"


typedef struct T9 { s16 v[9]; } T9;
typedef struct Lbl { s16 h0; s16 h2; void *p4; } Lbl;
typedef struct Box { s16 h0; s16 h2; s16 h4; s16 h6; s16 h8; s16 hA; s16 hC; s16 hE; } Box;
typedef struct Wnd { u8 pad[0x20]; Box *f20; u8 pad24[4]; Lbl *f28; } Wnd;
typedef struct Ent { u8 pad[3]; u8 kind; u8 pad4[4]; s32 f8; } Ent;

extern s32 GetGameData_1fede0(void);
extern s32 RevelationBoardGetCells_3eb510(s32, s32);
extern Ent *RevelationBoardCellGetValue_3eade0(s32, s32, s32 *);
extern Wnd *UiFindWidget_290460(s32, s32);
extern void Sprintf_1343b8(void *, void *, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern f32 Sinf_128fd0(f32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern T9 D_00453930;
extern T9 D_00453950;
extern T9 D_00453970;
extern T9 D_00453990;
extern u8 D_004628F8[];
extern f32 D_0047D278;
extern const f32 D_0047D400 __attribute__((section(".sdata")));
extern s32 D_0047F6C4;
extern s32 D_00482360;
extern u8 *D_0048238C;
extern s32 D_004823D8;
extern s16 D_00482E2C;
extern u8 D_004E8DA0[];

#define CP9(d, s) { s16 *s_ = (s).v; s16 *d_ = (d).v; s32 n_ = 9; do { n_--; *d_ = *s_; s_++; d_++; } while (n_ > 0); }
void RevelationBoardDrawCellInfoMaybe_348d60(void) {
    s32 cc;
    s32 c8;
    s32 c4;
    s32 c0;
    T9 ta;
    T9 tb;
    T9 tc;
    T9 td;
    s32 x;
    s16 *idx;
    s32 r;
    s32 *e;
    Ent *y;
    Wnd *w;
    Lbl *l;
    Box *b;
    s32 k;
    f32 t;

    x = GetGameData_1fede0();
    if (x == 0) return;
    idx = (s16 *)(D_0048238C + 0x10);
    r = RevelationBoardGetCells_3eb510(x, D_0047F6C4);
    if (r == 0) return;
    e = (s32 *)r + (idx[0] + idx[1] * 26);
    if (e == 0) return;
    y = RevelationBoardCellGetValue_3eade0(x, D_0047F6C4, e);
    D_00482E2C = (s16)(D_00482E2C + 1) % 60;
    if (y == 0) return;
    w = UiFindWidget_290460(D_00482360, 0x55);
    if (w == 0) return;
    l = w->f28;
    if (l == 0) return;
    Sprintf_1343b8(D_004E8DA0, D_004628F8, y->f8);
    l->p4 = D_004E8DA0;
    UiSetWidgetPos_290f60(D_00482360, 0x55, 0x1B, 0x2D);
    UiSetWidgetPos_290f60(D_00482360, 0x54, 0x6D, 0xBF);
    cc = 0;
    c8 = 0;
    c4 = 0;
    c0 = 0;
    UiGetWidgetPos_2910a0(D_00482360, 0x54, &cc, &c8);
    UiGetWidgetPos_2910a0(D_00482360, 0x55, &c4, &c0);
    UiSetTextCenteredX_28f300(D_00482360, 0x55, 0x100, 0);
    l->h0 -= (s16)(cc + c4);
    l->h0 += 12;
    if (l->h0 == -1) l->h0 = 0;
    b = w->f20;
    if (b == 0) return;
    CP9(ta, D_00453930);
    CP9(tb, D_00453950);
    CP9(tc, D_00453970);
    CP9(td, D_00453990);
    k = 0;
    switch (y->kind) {
    case 1: k = 1; break;
    case 2: k = 0; break;
    case 3: k = 2; break;
    case 4: k = 3; break;
    case 5: k = 4; break;
    case 11: k = 5; break;
    case 12: k = 6; break;
    case 13: k = 7; break;
    case 14: k = 8; break;
    }
    b->h0 = l->h0 - 0x1C;
    if (b->h0 == -1) b->h0 = 0;
    b->h2 = -1;
    b->h8 = ta.v[k];
    b->hA = tb.v[k];
    b->h4 = b->hC = tc.v[k];
    b->h6 = b->hE = td.v[k];
    t = D_0047D278 + Sinf_128fd0(D_0047D400 * (f32)D_00482E2C);
    UiSetWidgetColor_2905b0(D_00482360, 0x56, t, t, t, 1.0f);
    UiSetWidgetPos_290f60(D_00482360, 0x56, 0x89, -7);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x56, 1, 1);
    UiSetWidgetPos_290f60(D_00482360, 0x57, 0x82, (s32)(-24.0f - 3.0f * Sinf_128fd0(2.0f * (*(f32 *)&D_0047D400 * (f32)D_00482E2C))));
    UiSetWidgetsVisibleById_291110(D_00482360, 0x57, 1, 1);
    UiSetTextString_28f510(D_00482360, 0x54, MsgTableLookup_28aa30(D_004823D8, 0x1036), 0);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x54, 1, 1);
}
