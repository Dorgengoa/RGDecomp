#include "types.h"

/* insmenu 0x004F68D0 (260 bytes) -- the caption-placement twin of
 * insmenu_InsectVsLoadYesNoCursorBob_4f69e0 sixteen bytes later: same show/hide guard, same eased
 * lift, but it measures with func_376FD0 and then either sets the position or
 * fades it in at full alpha.
 *
 * ★ The hide arm RETURNS, so the show arm is the fall-through and the gp float
 * load for the next call rides the `b` out of it.
 * ★ `mtc1 $2, $f12` off `lui 0x3F80` is the literal `1.0f`. */

extern const u8 D_004FA180[];
extern f32 D_0047D3B8;          /* gp - 0x7DB8 */
extern f32 D_0048434C;          /* gp - 0xE24 */

extern void func_290010(const void *a, s32 id, s32 c, s32 d);
extern void func_28B630(f32 *p, f32 v);
extern f32  func_128FD0(f32 x);
extern void func_376FD0(const void *a, void *b, s32 *x, s32 *y);
extern void func_290F60(const void *a, s32 id, s32 x, s32 y);
extern void func_290F50(const void *a, s32 id, s32 x, s32 y, s32 e, f32 t);

void insmenu_InsectVsLoadPortCursorBob_4f68d0(void *obj, s32 place, s32 show)
{
    f32 lift;
    s32 x;
    s32 y;

    if (show) {
        func_290010(D_004FA180, 0x890A, 1, -1);
    } else {
        func_290010(D_004FA180, 0x890A, 0, -1);
        return;
    }
    func_28B630(&D_0048434C, D_0047D3B8);
    lift = 6.0f * func_128FD0(D_0048434C);
    func_376FD0(D_004FA180, obj, &x, &y);
    x = (s32)((f32)x + lift);
    if (place) {
        func_290F60(D_004FA180, 0x890A, x, y);
    } else {
        func_290F50(D_004FA180, 0x890A, x, y, 0, 1.0f);
    }
}
