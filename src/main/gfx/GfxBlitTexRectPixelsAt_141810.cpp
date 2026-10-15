#include "types.h"

typedef struct Rect {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
} Rect;

extern "C" void GfxBlitTexRect_141000(s32 arg0, s32 arg1, Rect *src, s32 arg3, Rect *dst);

extern "C" void GfxBlitTexRectPixelsAt_141810(s32 arg0, s32 arg1, Rect *src, s32 arg3, s32 y, s32 x)
{
    Rect a;
    Rect b;
    s32 x1;
    s32 y1;

    if (arg1 == 0 || arg3 == 0) {
        return;
    }
    x1 = x + (src->x1 - src->x0);
    y1 = y + (src->y1 - src->y0);
    a = *src;
    b.x0 = x;
    b.y0 = y;
    b.x1 = x1;
    b.y1 = y1;
    a.y0 = a.y0 * 16;
    a.y1 = a.y1 * 16;
    a.x0 = a.x0 * 16;
    a.x1 = a.x1 * 16;
    b.y0 = b.y0 * 16;
    b.y1 = b.y1 * 16;
    b.x0 = b.x0 * 16;
    b.x1 = b.x1 * 16;
    GfxBlitTexRect_141000(arg0, arg1, &a, arg3, &b);
}
