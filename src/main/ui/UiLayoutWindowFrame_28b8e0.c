#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 minw;
    s16 minh;
    s16 w0;
    s16 h0;
    u8 pad10[0x10];
} Elem;

#define RESET(r) ((r).w = (r).w0, (r).h = (r).h0)

void UiLayoutWindowFrame_28b8e0(Elem *e, s32 width, s32 height, s32 n) {
    Elem *e3;
    s32 q;
    s32 i;
    s32 w;
    s32 y;

    if (e == 0) {
        return;
    }
    e3 = &e[3];
    RESET(e[0]);
    e[0].w = 8;
    e[0].minw = e[1].minw + 8;
    e[0].w0 = e[0].w;
    e[0].x = width - 8;
    e[0].y = 0;
    RESET(e[1]);
    e[1].x = width - e[1].w;
    e[1].y = e[0].h;
    e[1].h = height - (e[0].h + e[2].h);
    RESET(e[2]);
    e[2].x = width - e[2].w;
    e[2].y = e[1].y + e[1].h;
    RESET(e[3]);
    e += 4;
    q = (height - 12) / n;
    for (i = 0; i < n; i++) {
        RESET(*e);
        e->x = 6;
        e->y = i * (q + 1) + 6;
        e->w = width - 12;
        e->h = q;
        e++;
    }
    for (i = 0; i < n - 1; i++) {
        RESET(*e);
        e->x = 4;
        e->y = (i + 1) * (q + 1) + 2;
        e->w = width - 8;
        e++;
    }
    w = e[0].w;
    e[0].x = 0;
    e[0].y = 0;
    RESET(e[1]);
    e[1].x = 0;
    e[1].y = e[0].h;
    e[1].h = height - (e[0].h + e[2].h);
    RESET(e[2]);
    y = e[1].y + e[1].h;
    e[2].x = 0;
    e[2].y = y;
    e3->h = 8;
    e3->minh = e[4].minh + 8;
    e3->h0 = e3->h;
    e3->x = 0;
    e3->y = y + 8;
    RESET(e[3]);
    e[3].x = w;
    e[3].y = 0;
    e[3].w = width - (w + e[5].w);
    RESET(e[4]);
    e[4].x = w;
    e[4].y = y;
    e[4].w = width - (w + e[6].w);
    RESET(e[5]);
    e[5].x = width - e[5].w;
    e[5].y = 0;
    RESET(e[6]);
    e[6].x = width - e[6].w;
    e[6].y = e[5].h;
    e[6].h = height - (e[5].h + e[7].h);
    RESET(e[7]);
    e[7].x = width - e[7].w;
    e[7].y = e[6].y + e[6].h;
}
