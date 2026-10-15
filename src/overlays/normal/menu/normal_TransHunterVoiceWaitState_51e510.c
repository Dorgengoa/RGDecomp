#include "types.h"
/* normal 0x0051E510 -- twin of normal_FUN_0051EA30.  Sibling of the settled
 * seed normal_FUN_0051E5F0 (same widget family, same 0x7919 id, same
 * `extern f32 D_0047D9C0` gp float spelling).
 *
 * The `daddu $16,$2,$0` in func_207290's DELAY SLOT captures func_2072C0's
 * return, so the two calls are two locals evaluated BEFORE the || chain --
 * that is why func_207290 is not short-circuited.  func_207290 returns a f32
 * in $f0 (its $2 is unused).
 */

extern void *D_0048470C;          /* gp - 0xA64 */
extern void *D_00484710;          /* gp - 0xA60 */
extern void *D_00484718;          /* gp - 0xA58 */
extern f32   D_0047D9C0;          /* gp - 0x77B0 */

extern void  func_2072F0(s32 a, f32 t);
extern s32   func_2072C0(void);
extern f32   func_207290(void);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);
extern void *func_1F59D0(void);
extern void  func_1CD960(void *p, s32 a, s32 b, f32 t);
extern void  func_28EDE0(void *w, s32 id, s32 a);

s32 normal_TransHunterVoiceWaitState_51e510(void *a, s32 b)
{
    s32 st;
    f32 t;

    if (b != 0) {
        func_2072F0(0xF, 0.0f);
        func_290690(D_00484718, 0x7919, 0.0f, D_0047D9C0, -1.0f);
        func_291110(D_00484710, 0x7633, 0, 1);
    }
    st = func_2072C0();
    t = func_207290();
    if (st == -2 || st == 0 || st == 2 || t <= 0.0f) {
        func_1CD960(func_1F59D0(), 0, 0xF, 1.0f);
        func_28EDE0(D_0048470C, 0x19, 0);
    }
    return 1;
}
