#include "types.h"

typedef struct Pnl {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 m8;
    s16 fl;
    s32 mC;
    f32 sx;
    f32 sy;
    u8 pad18[8];
} Pnl;

void UiLayoutPanelFrame_28d580(Pnl *p, s32 x, s32 y, s32 w, s32 h, s32 mode)
{
    p[0].x = x + 20;
    p[0].y = y + 23;
    p[0].sx = (f32)(w - 30) / (f32)p[0].w;
    p[0].sy = (f32)(h - 33) / (f32)p[0].h;
    switch (mode) {
    case 0:
        p[0].fl = 0;
        break;
    case 1:
        p[0].fl = 0x40;
        break;
    }
    p[1].x = x;
    p[1].y = y;
    p[2].x = x;
    p[2].y = p[1].y + p[1].h;
    p[2].sy = (f32)(h - p[1].h - p[3].h) / (f32)p[2].h;
    p[3].x = x;
    p[3].y = p[2].y + (h - p[1].h - p[3].h);
    p[4].x = x + p[1].w;
    p[4].y = y;
    p[4].sx = (f32)(w - p[1].w - p[7].w) / (f32)p[4].w;
    p[5].x = p[4].x;
    p[5].y = p[3].y;
    p[5].sx = (f32)(p[6].w * -2 - p[10].w - p[3].w - -w) / (f32)p[5].w;
    p[6].x = p[6].w * -2 - p[10].w - p[3].w - -w - -p[4].x;
    p[6].y = p[3].y;
    p[6].sx = 2.0f;
    p[7].x = p[4].x + (w - p[1].w - p[7].w);
    p[7].y = y;
    p[8].x = p[7].x;
    p[8].y = y + p[7].h;
    p[8].sy = (f32)(p[9].h * -2 - p[10].h - p[7].h - -h) / (f32)p[8].h;
    p[9].x = p[7].x + 1;
    p[9].y = p[9].h * -2 - p[10].h - p[7].h - -h - -p[8].y;
    p[9].sy = 2.0f;
    p[10].x = p[7].x;
    p[10].y = p[9].y + p[9].h * 2;
}
