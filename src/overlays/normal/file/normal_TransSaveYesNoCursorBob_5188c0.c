#include "types.h"
/* normal 0x005188C0 -- the gauge publisher.  `ori $5,$0,0x80EC` (not addiu) is
 * the u16 id.  The two stack ints live at sp+0x3C and sp+0x38 and are written
 * back after the float bias, which is why 0x3C is re-stored. */

extern void *D_00484714;   /* gp - 0xA5C  */
extern f32   D_004847E4;   /* gp - 0x98C  */

extern void func_290010(void *w, u16 id, s32 a, s32 b);
extern void func_28B630(f32 *out, f32 v);
extern f32  func_128FD0(f32 x);
extern void func_3770B0(void *w, s32 a, s32 *x, s32 *y);
extern void func_290F60(void *w, u16 id, s32 x, s32 y);
extern void func_3773A0(void *w, s32 a);

void normal_TransSaveYesNoCursorBob_5188c0(s32 a, s32 b, s32 c)
{
    s32 x;
    s32 y;
    f32 bias;

    if (c != 0) {
        func_290010(D_00484714, 0x80EC, 1, -1);
    } else {
        func_290010(D_00484714, 0x80EC, 0, -1);
        return;
    }
    func_28B630(&D_004847E4, 0.078539818525314331f);
    bias = 6.0f * func_128FD0(D_004847E4);
    x = 0;
    y = 0;
    func_3770B0(D_00484714, a, &x, &y);
    x = (s32)((f32)x + bias);
    func_290F60(D_00484714, 0x80EC, x, y);
    func_3773A0(D_00484714, a);
}
