#include "types.h"
/* normal 0x00510620 -- same func_28B630 / func_128FD0 scale as 0x005097E0,
 * feeding a two-out-parameter measure whose second result is clamped to 0x100.
 * The two stack locals are declared in the order that puts the first at the
 * HIGHER offset (mwcc allocates locals in reverse declaration order). */
extern f32 D_00484678;                /* gp - 0xAF8  */
extern const u8 D_00527E70[];

extern void func_28B630(f32 *out, f32 x);
extern f32  func_128FD0(f32 x);
extern void func_28ECD0(void *p, s32 *ox, s32 *oy, s32 n, s32 m);
extern void func_290F50(void *p, u16 id, s32 a, s32 b, s32 c, f32 x);
extern void func_28D820(const void *p, s32 id);

s32 normal_ShopMenuSellGridCursorBobCb_510620(void *p, void *w)
{
    s32 vx;
    s32 vy;
    f32 t;

    func_28B630(&D_00484678, 0.07853981853f);
    t = 6.0f * func_128FD0(D_00484678);
    func_28ECD0(p, &vx, &vy, (s32)t, 0);
    if (vy > 0x100) {
        vy = 0x100;
    }
    func_290F50(w, 0x40, vx, (s32)((f32)vy + t), 0, 0.25f);
    func_28D820(D_00527E70, 0x3F);
    return 1;
}
