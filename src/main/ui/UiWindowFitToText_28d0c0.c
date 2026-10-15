#pragma optimization_level 3
#include "types.h"

typedef struct Spr {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u8 pad[0x18];
} Spr;

typedef struct Hdr {
    s16 x;
    s16 y;
    u8 pad[6];
    s8 font;
} Hdr;

typedef struct Win {
    Spr *cur;
    Hdr *hdr;
    s32 x;
    s32 y;
    s32 padw;
    s32 padh;
    s32 hx;
    s32 hy;
    s32 bx;
    s32 by;
    s32 bw;
    s32 bh;
    u16 flags;
} Win;

s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetWidth_1451e0(s32);
s32 GetDrawCtx_15de80();
void TextStyleInit_26c610(void *);
void FontMeasureString_26daf0(void *, s32, s32 *, s32 *);
void TextStyleInitWithFontType_2931c0(void *, s32);

void UiWindowFitToText_28d0c0(Win *self, s32 *str, s32 n, s32 *adj) {
    u8 fnt[0x40];
    s32 w;
    s32 h;
    s32 lw;
    s32 lh;
    s32 i;
    s32 scr;
    s32 x;
    s32 y;
    s32 x16;
    s32 y16;
    s32 xr;
    s32 yb;

    TextStyleInit_26c610(fnt);
    TextStyleInitWithFontType_2931c0(fnt, self->hdr->font);
    FontMeasureString_26daf0(fnt, *(s32 *)((u8 *)self->hdr + 4), &w, &h);
    for (i = 0; i < n; i++, str++) {
        if (*str != 0) {
            FontMeasureString_26daf0(fnt, *str, &lw, &lh);
            if (adj != NULL) {
                lw += *adj++;
            }
            if (w < lw) {
                w = lw;
            }
        }
    }
    if (self->flags & 8) {
        w = self->padw;
    } else {
        w += self->padw;
    }
    h += self->padh;
    scr = GetDrawCtx_15de80();
    if (self->flags & 1) {
        x = self->x;
    } else {
        x = DrawEnvGetWidth_1451e0(scr) / 2 - w / 2;
    }
    if (self->flags & 2) {
        y = self->y;
    } else {
        y = DrawEnvGetHeight_1451d0(scr) / 2 - h / 2;
    }
    if (self->flags & 4) {
        x = self->bx + (self->bw / 2 - w / 2);
        y = self->by + (self->bh / 2 - h / 2);
    }
    w -= 0x20;
    h -= 0x20;
    if (w < 0) {
        w = 0;
    }
    if (h < 0) {
        h = 0;
    }
    x16 = x + 0x10;
    xr = x16 + w;
    y16 = y + 0x10;
    yb = y16 + h;
    self->hdr->x = x + self->hx;
    self->hdr->y = y + self->hy;
    self->cur->x = xr;
    self->cur->y = y;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = xr;
    self->cur->y = y16;
    self->cur->w = 0x10;
    self->cur->h = h;
    self->cur++;
    self->cur->x = xr;
    self->cur->y = yb;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = x;
    self->cur->y = yb;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = x + 6;
    self->cur->y = y + 6;
    self->cur->w = w + 0x15;
    self->cur->h = h + 0x15;
    self->cur++;
    self->cur->x = x;
    self->cur->y = y;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = x;
    self->cur->y = y16;
    self->cur->w = 0x10;
    self->cur->h = h;
    self->cur++;
    self->cur->x = x;
    self->cur->y = yb;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = x16;
    self->cur->y = y;
    self->cur->w = w;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = x16;
    self->cur->y = yb;
    self->cur->w = w;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = xr;
    self->cur->y = y;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
    self->cur++;
    self->cur->x = xr;
    self->cur->y = y16;
    self->cur->w = 0x10;
    self->cur->h = h;
    self->cur++;
    self->cur->x = xr;
    self->cur->y = yb;
    self->cur->w = 0x10;
    self->cur->h = 0x10;
}
