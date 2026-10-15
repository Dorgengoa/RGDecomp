/* libdeasm dark7 2026-10-12: C staged by the PC-port session, __MWERKS__ branch kept,
 * port names respelled to the retail glabel names; header below is the port's own note. */
/* rg-missing: UiNineSliceSpritesLayout_3930d0 (retail MAIN 0x003930D0, size 0x400)
 * why: the INSECT battle UI (insect_InsectBattleHelpStep_50a9f0,
 * insect_InsectBattleMenuTeamSelect_5004f0) calls it as func_3930D0; retail has a
 * whole leaf function there (glabel UiNineSliceSpritesLayout_3930d0), no C in
 * the snapshot.  Lays out a 9-slice window: cell 0 is the fill quad (mode 1..4
 * picks its UV), cells 1..9 the frame pieces.  Sibling of
 * InsectBattleMenuFrameNineSliceMaybe_393ac0 / UiNineSliceLayoutMaybe_392440.
 * Checked: mwcc 3.0.1b210 -O4 -sdatathreshold 16 compiles this file to retail's
 * 254 instructions (MATCH, out/missing-staged/README.md); the six f32/s32[3]
 * initialiser templates equal retail .sdata D_0047FD60..D_0047FDB8. */
#include "types.h"
#pragma divbyzerocheck on

typedef struct Cell {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 uw;
    s16 vh;
    f32 sx;
    f32 sy;
    s16 mx;
    s16 my;
    s16 flag;
    u8 pad1E[2];
} Cell;

typedef struct Win {
    u8 pad0[0x20];
    Cell *cells;
} Win;


void UiNineSliceSpritesLayout_3930d0(s32 unused, Win *win, s32 w, s32 h, s32 mode)
{
    Cell *c;
    Cell *p;
    s32 i;
    s32 k;

    if (win == 0) {
        return;
    }
    p = win->cells;
    if (p == 0) {
        return;
    }
    for (i = 0; i < 10; i++, p++) {
        p->x = p->y = 0;
        p->w = p->uw = 0;
        p->h = p->vh = 0;
        p->u = p->v = 0;
        p->mx = p->my = 0;
        p->sx = p->sy = p->mx;
    }
    c = win->cells;
    c->x = c->y = 2;
    switch (mode) {
    case 0:
        break;
    case 1:
        c->w = w;
        c->h = h;
        c->uw = 4;
        c->vh = 4;
        c->sy = 0.0f;
        c->mx = c->my = c->sy;
        c->sx = c->mx;
        c->u = 0x34;
        c->v = 0x8C;
        break;
    case 2:
        c->w = w;
        c->h = h;
        c->uw = 2;
        c->vh = 0x18;
        c->sy = 0.0f;
        c->mx = c->my = c->sy;
        c->sx = c->mx;
        c->u = 0xFC;
        c->v = 0x24;
        break;
    case 3:
        c->w = w;
        c->h = h;
        c->uw = 2;
        c->vh = 0x18;
        c->sy = 0.0f;
        c->mx = c->my = c->sy;
        c->sx = c->mx;
        c->u = 0xF8;
        c->v = 0x24;
        break;
    case 4:
        c->w = w;
        c->h = h;
        c->uw = 2;
        c->vh = 0x18;
        c->sy = 0.0f;
        c->mx = c->my = c->sy;
        c->sx = c->mx;
        c->u = 0xF4;
        c->v = 0x24;
        break;
    }
    p = c + 1;
    for (k = 0; k < 9; k++, p++) {
        s32 col = k % 3;
        s32 row = k / 3;
        f32 X[3] = {0.0f, 8.0f, 0.0f + 8.0f + 8.0f * (((f32)w - 26.0f) / 8.0f)};
        f32 Y[3] = {0.0f, 36.0f, 0.0f + 36.0f + 8.0f * (((f32)h - 44.0f) / 8.0f)};
        s32 W[3] = {8, 8, 18};
        s32 H[3] = {36, 8, 8};
        s32 U[3] = {0, 8, 16};
        s32 V[3] = {122, 158, 166};
        if (col == 1 && row == 1) {
            continue;
        }
        p->x = (s32)X[col];
        p->y = (s32)Y[row];
        p->w = p->uw = W[col];
        p->h = p->vh = H[row];
        p->u = U[col];
        p->v = V[row];
        if (col == 1) {
            p->w = w - W[0] - W[2];
        }
        if (row == 1) {
            p->h = h - H[0] - H[2];
        }
    }
}

