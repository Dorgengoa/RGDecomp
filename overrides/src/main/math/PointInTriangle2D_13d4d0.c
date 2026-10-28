/* rg-override: replaces game/src/main/math/PointInTriangle2D_13d4d0.c sha256 6537a2a0bdc320a18f28bb551c9982aab3b03a8e9ac96d29ddac0ee64eb2229a
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* 2D point-in-triangle for (px, py) against (ax, ay), (bx, by), (cx, cy).
   Returns 0 outside the bounding box or outside the triangle, 2/3/4 when the
   point is on the line of edge ab/bc/ca (edge function == 0), 1 inside.
   The listing returns $2; the one caller declares it void. */
s32 PointInTriangle2D_13d4d0(f32 px, f32 py, f32 ax, f32 ay, f32 bx, f32 by, f32 cx, f32 cy)
{
    f32 m, e0, e1, e2;

    /* min x */
    if (ax < bx)
        m = (ax < cx) ? ax : cx;
    else
        m = (bx < cx) ? bx : cx;
    if (!(m <= px))
        return 0;
    /* max x */
    if (!(ax <= bx))
        m = (ax <= cx) ? cx : ax;
    else
        m = (bx <= cx) ? cx : bx;
    if (!(px <= m))
        return 0;
    /* min y */
    if (ay < by)
        m = (ay < cy) ? ay : cy;
    else
        m = (by < cy) ? by : cy;
    if (!(m <= py))
        return 0;
    /* max y */
    if (!(ay <= by))
        m = (ay <= cy) ? cy : ay;
    else
        m = (by <= cy) ? cy : by;
    if (!(py <= m))
        return 0;

    /* mula.s / msub.s: ACC = a * b, then ACC - c * d (two rounded products) */
    e0 = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
    e1 = (cx - bx) * (py - by) - (cy - by) * (px - bx);
    e2 = (ax - cx) * (py - cy) - (ay - cy) * (px - cx);
    if (0.0f == e0)
        return 2;
    if (0.0f == e1)
        return 3;
    if (0.0f == e2)
        return 4;
    if (!(e0 <= 0.0f) && !(e1 <= 0.0f) && !(e2 <= 0.0f))
        return 1;
    if (!(e0 < 0.0f))
        return 0;
    if (!(e1 < 0.0f))
        return 0;
    if (!(e2 < 0.0f))
        return 0;
    return 1;
}
