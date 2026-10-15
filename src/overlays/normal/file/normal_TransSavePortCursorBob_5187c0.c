#include "types.h"
/* normal 0x005187C0 -- the 0x80EC gauge.  The `c == 0` arm returns through the
 * far epilogue, so the function is void.  The 6.0f product is NAMED (f20) --
 * that is what keeps the `cvt.w.s` on the plain path and the `add.s` operands
 * in retail's order.  The float in the `b` delay slot is func_28B630's $f12
 * argument, not a dead load. */

extern void *D_00484714;          /* gp - 0xA5C */
extern f32   D_0047D3B8;          /* gp - 0x7DB8 */
extern f32   D_004847E4;          /* gp - 0x98C */

extern void func_290010(void *p, u16 id, s32 c, s32 d);
extern void func_28B630(f32 *p, f32 x);
extern f32  func_128FD0(f32 x);
extern void func_376FD0(void *p, s32 a, s32 *outX, s32 *outY);
extern void func_290F60(void *p, u16 id, s32 c, s32 d);
extern void func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);

void normal_TransSavePortCursorBob_5187c0(s32 a, s32 b, s32 c)
{
    s32 x;
    s32 y;
    f32 t;

    if (c != 0) {
        func_290010(D_00484714, 0x80EC, 1, -1);
    } else {
        func_290010(D_00484714, 0x80EC, 0, -1);
        return;
    }
    func_28B630(&D_004847E4, D_0047D3B8);
    t = 6.0f * func_128FD0(D_004847E4);
    x = 0;
    y = 0;
    func_376FD0(D_00484714, a, &x, &y);
    x = (s32)((f32)x + t);
    if (b != 0) {
        func_290F60(D_00484714, 0x80EC, x, y);
    } else {
        func_290F50(D_00484714, 0x80EC, x, y, 0, 0.25f);
    }
}
