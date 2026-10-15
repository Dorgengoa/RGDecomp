#include "types.h"

/* insmenu 0x004F69E0 (220 bytes) -- show or hide the insect-menu caption, and
 * when showing it, nudge its Y by the eased fade value.
 *
 * ★ The hide arm RETURNS, so the show arm is the fall-through and the common
 * tail belongs to the show path only; retail's `b` out of the show arm carries
 * the gp float load for the next call in its delay slot.
 * ★ `lwc1 $f0` on a slot that func_3770B0 filled with an INTEGER, followed by
 * cvt.s.w, is a plain `(f32)x` on an s32 out-parameter. */

extern const u8 D_004FA180[];
extern f32 D_0047D3B8;          /* gp - 0x7DB8 */
extern f32 D_0048434C;          /* gp - 0xE24 */

extern void func_290010(const void *a, s32 id, s32 c, s32 d);
extern void func_28B630(f32 *p, f32 v);
extern f32  func_128FD0(f32 x);
extern void func_3770B0(const void *a, void *b, s32 *x, s32 *y);
extern void func_290F60(const void *a, s32 id, s32 x, s32 y);
extern void func_3773A0(const void *a, void *b);

void insmenu_InsectVsLoadYesNoCursorBob_4f69e0(void *obj, s32 b, s32 show)
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
    func_3770B0(D_004FA180, obj, &x, &y);
    x = (s32)((f32)x + lift);
    func_290F60(D_004FA180, 0x890A, x, y);
    func_3773A0(D_004FA180, obj);
}
