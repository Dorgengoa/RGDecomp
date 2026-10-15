#include "types.h"
/* normal 0x005209C0 -- advance the shared phase by 0.1570796f, take its sine,
 * scale by 6.0 and offset the two integer arguments by it.  The product
 * 6.0f * sinf(phase) is used twice, so it is a NAMED local -- that is what
 * keeps the `mul.s` out of a madd and fixes the add.s operand order.
 * 0x0047D3D0 is a mwcc .lit4 POOL ENTRY, so it must be spelled as the float
 * LITERAL -- an `extern f32` load is pinned below the callee-saved `sq`
 * stores and rotates the whole prologue by one slot. */

extern f32 D_00484944;            /* gp - 0x82C */

extern void func_28B630(f32 *p, f32 d);
extern f32  func_128FD0(f32 x);
extern void func_28ECD0(void *a, s32 *ox, s32 *oy, s32 x, s32 y);
extern void func_290F50(void *w, u16 id, s32 x, s32 y, s32 z, f32 t);

s32 normal_ThinkMenuGridCursorBobToCell_5209c0(void *a, void *b, s32 c, s32 d)
{
    s32 ox;
    s32 oy;
    f32 s;

    func_28B630(&D_00484944, 0.1570796371f);
    s = 6.0f * func_128FD0(D_00484944);
    func_28ECD0(a, &ox, &oy, (s32)(s + (f32)c), (s32)(s + (f32)d));
    func_290F50(b, 0x7544, ox, oy, 0, 0.5f);
    return 1;
}
