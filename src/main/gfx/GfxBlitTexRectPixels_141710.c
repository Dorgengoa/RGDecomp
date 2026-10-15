#include "types.h"

extern void GfxBlitTexRect_141000(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 *arg4);

void GfxBlitTexRectPixels_141710(s32 arg0, s32 arg1, s32 *p, s32 arg3, s32 *q) {
    s32 a[4];
    s32 b[4];

    a[0] = p[0];
    a[1] = p[1];
    a[2] = p[2];
    a[3] = p[3];
    b[0] = q[0];
    b[1] = q[1];
    b[2] = q[2];
    b[3] = q[3];
    a[1] = a[1] * 16;
    a[3] = a[3] * 16;
    a[0] = a[0] * 16;
    a[2] = a[2] * 16;
    b[1] = b[1] * 16;
    b[3] = b[3] * 16;
    b[0] = b[0] * 16;
    b[2] = b[2] * 16;
    GfxBlitTexRect_141000(arg0, arg1, a, arg3, b);
}
