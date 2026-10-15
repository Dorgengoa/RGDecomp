#include "types.h"

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

f32 UiScrollBarSpritesLayoutMaybe_392e60(s32 unused, Win *win, s32 h, s32 pos, s32 total)
{
    Cell *p;
    s32 i;
    f32 fh;
    f32 t;
    f32 r;

    if (win == 0) {
        return 0.0f;
    }
    p = win->cells;
    if (p == 0) {
        return 0.0f;
    }
    fh = (f32)h;
    {
    static f32 V[3] = {248.0f, 248.0f, 248.0f};
    static f32 U[3] = {74.0f, 80.0f, 88.0f};
    static f32 S[3] = {8.0f, 8.0f, 8.0f};
    static f32 E[3] = {6.0f, 8.0f, 6.0f};
    f32 H[3] = {6.0f, fh - 12.0f, 6.0f};
    f32 Y[3] = {0.0f, 6.0f, fh - 6.0f};
    r = 0.0f;
    if (pos < total) {
        t = fh * ((f32)pos / (f32)total);
        r = (fh - t) / (f32)(total - pos);
        Y[2] = t - E[2];
        H[1] = t - E[0] - E[2];
    }
    for (i = 0; i < 3; i++, p++) {
        p->x = 0;
        p->y = (s32)Y[i];
        p->w = (s32)S[i];
        p->h = (s32)H[i];
        p->u = (s32)V[i];
        p->v = (s32)U[i];
        p->uw = (s32)S[i];
        p->vh = (s32)E[i];
        p->mx = p->my = 0;
        p->sx = p->sy = p->mx;
    }
    }
    return r;
}
