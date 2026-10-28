/* rgp:protos */
#define RGP_SELF_InsectBattleMenuFrameNineSliceMaybe_393ac0 1
#include "port/game_protos.h"
#line 1
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

void InsectBattleMenuFrameNineSliceMaybe_393ac0(s32 unused, Win *win, s32 w, s32 h, s32 mode)
{
    Cell *c;
    Cell *p;
    s32 i;
    f32 fw;
    f32 fh;
    f32 sx;
    f32 sy;
    s32 col;
    s32 row;
    f32 hw;
    s32 t;
    s32 k;

    if (win == 0) {
        return;
    }
    c = win->cells;
    p = c;
    if (c == 0) {
        return;
    }
    for (i = 0; i < 10; i++, p++) {
        p->x = p->y = -1;
        p->u = p->v = 0;
        p->h = p->vh = 0;
        p->w = p->uw = 0;
        p->mx = p->my = 0;
        p->sx = p->sy = p->mx;
    }
    fw = (f32)(w - 0x20);
    fh = (f32)(h - 0x20);
    sx = fw / 8.0f;
    sy = fh / 8.0f;
    if (fw <= 0.0f) {
        sx = 0.0f;
    }
    if (fh <= 0.0f) {
        sy = 0.0f;
    }
    {
    f32 X[3] = {0.0f, 16.0f, 0.0f + 16.0f + 8.0f * sx};
    f32 Y[3] = {0.0f, 16.0f, 0.0f + 16.0f + 8.0f * sy};
    f32 U[3] = {0.0f, 16.0f, 24.0f};
    f32 V[3] = {0.0f, 16.0f, 24.0f};
    f32 S[3] = {16.0f, 8.0f, 16.0f};
    c->x = 2;
    c->y = 2;
    hw = (f32)((w - 4) / 2);
    switch (mode) {
    case 0:
        break;
    case 1:
        hw = (f32)((w - 8) / 4);
        t = h - 8;
        c->uw = 4;
        c->w = 4;
        c->mx = 4;
        c->vh = 4;
        c->h = 4;
        c->my = 4;
        c->u = 0x34;
        c->v = 0x8C;
        *(s32 *)&c->sx = 0;
        *(s32 *)&c->sy = 0;
        c->w = (s32)(4.0f * hw);
        c->h = (s32)(4.0f * (f32)(t / 4));
        break;
    case 2:
        c->uw = 2;
        c->w = 2;
        c->mx = 2;
        c->vh = 0x18;
        c->my = 0x18;
        c->u = 0xFC;
        c->v = 0x24;
        *(s32 *)&c->sx = 0;
        *(s32 *)&c->sy = 0;
        c->w = (s32)(2.0f * hw);
        c->h = h - 4;
        break;
    case 3:
        c->uw = 2;
        c->w = 2;
        c->mx = 2;
        c->vh = 0x18;
        c->my = 0x18;
        c->u = 0xF8;
        c->v = 0x24;
        *(s32 *)&c->sx = 0;
        *(s32 *)&c->sy = 0;
        c->w = (s32)(2.0f * hw);
        c->h = h - 4;
        break;
    case 4:
        c->uw = 2;
        c->w = 2;
        c->mx = 2;
        c->vh = 0x18;
        c->my = 0x18;
        c->u = 0xF4;
        c->v = 0x24;
        *(s32 *)&c->sx = 0;
        *(s32 *)&c->sy = 0;
        c->w = (s32)(2.0f * hw);
        c->h = h - 4;
        break;
    }
    c->flag = 0;
    p = c + 1;
    for (k = 0; k < 9; k++, p++) {
        col = k % 3;
        row = k / 3;
        p->x = (s32)X[col];
        p->y = (s32)Y[row];
        p->u = (s32)(78.0f + U[col]);
        p->v = (s32)(122.0f + V[row]);
        p->uw = (s32)S[col];
        p->w = (s32)S[col];
        p->vh = (s32)S[row];
        p->h = (s32)S[row];
        p->flag = 0;
        if (row == 1 && col == 1) {
            p->uw = 0;
            p->w = 0;
            p->vh = 0;
            p->h = 0;
        } else {
            if (col == 1) {
                if (!(sx <= 0.0f)) {
                    p->sx = sx;
                    p->mx = 8;
                } else {
                    p->uw = 0;
                    p->w = 0;
                    p->vh = 0;
                    p->h = 0;
                    p->v = 0;
                    p->u = 0;
                }
            }
            if (row == 1) {
                if (!(sy <= 0.0f)) {
                    p->sy = sy;
                    p->my = 8;
                } else {
                    p->uw = 0;
                    p->w = 0;
                    p->vh = 0;
                    p->h = 0;
                    p->v = 0;
                    p->u = 0;
                }
            }
        }
    }
    p->x = -1;
    }
}
