#include "types.h"
/* normal 0x005097E0 -- places the 0x30 widget from the box's own extents.
 * func_28B630 writes the gp scalar D_004845E8 (address-taken, so it must stay
 * under the small-data threshold) and func_128FD0 reads it back as a float.
 * The scale product is NAMED, which is what makes the single `mul.s $f2` and
 * the two `add.s` chains come out instead of a contraction. */
typedef struct Box { s16 f00; s16 f02; s16 f04; s16 f06; u8 pad08[8]; s16 f10; s16 f12; } Box;

extern f32 D_004845E8;                /* gp - 0xB88  */

extern void func_28B630(f32 *out, f32 x);
extern f32  func_128FD0(f32 x);
extern void func_290F50(void *p, u16 id, s32 a, s32 b, s32 c, f32 x);

s32 normal_ShopMenuCursorBob_5097e0(Box *o, void *w, s32 c, s32 d)
{
    f32 t;

    func_28B630(&D_004845E8, 0.07853981853f);
    t = 6.0f * func_128FD0(D_004845E8);
    func_290F50(w, 0x30,
                (s32)((f32)c + (t + (f32)(o->f00 + o->f10 * o->f04))),
                (s32)((f32)o->f12 + ((f32)d + (t + (f32)(o->f02 + o->f12 * o->f06)))),
                0, 0.25f);
    return 1;
}
