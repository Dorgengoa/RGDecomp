#include "types.h"
/* normal 0x00518990 -- same 6.0f bias as 0x005188C0, but the bias is passed as
 * an INT argument to func_28ECD0 and the tail splits on the third parameter
 * between the 4-arg func_290F60 and the 6-arg func_290F50 (5 ints $4-$8 plus
 * one float in $f12). */

extern f32 D_004847E4;   /* gp - 0x98C  */

extern void func_28B630(f32 *out, f32 v);
extern f32  func_128FD0(f32 x);
extern void func_28ECD0(void *w, s32 *x, s32 *y, s32 n, s32 f);
extern void func_290F60(void *w, u16 id, s32 x, s32 y);
extern void func_290F50(void *w, u16 id, s32 x, s32 y, s32 f, f32 v);

void normal_TransSaveSlotCursorBob_518990(void *a, void *b, s32 c)
{
    s32 x;
    s32 y;

    func_28B630(&D_004847E4, 0.078539818525314331f);
    func_28ECD0(a, &x, &y, (s32)(6.0f * func_128FD0(D_004847E4)), 0);
    if (c != 0) {
        func_290F60(b, 0x75A2, x, y);
    } else {
        func_290F50(b, 0x75A2, x, y, 0, 0.25f);
    }
}
