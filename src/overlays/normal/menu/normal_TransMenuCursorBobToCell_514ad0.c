#include "types.h"
/* normal 0x00514AD0 -- the scaled-offset placement call.  `6.0f * f` is NAMED
 * (the float-product lever) so the madd contraction and the IEEE fptosi path
 * both go away; the two conversions then come out as plain `cvt.w.s`.
 * `lwc1 $f12,-0x7DB8($28)` is the POOL ENTRY 0x0047D3B8 = 0.078539819f (pi/40);
 * written as an `extern f32` its load is PINNED and sinks below the callee-saved
 * saves -- only the LITERAL reproduces retail's schedule. */

typedef struct Obj { u8 pad00[0x12]; s16 f12; } Obj;

extern f32 D_00484780;            /* gp - 0x9F0  */

extern void func_28B630(f32 *out, f32 v);
extern f32  func_128FD0(f32 v);
extern void func_28ECD0(Obj *p, s32 *ox, s32 *oy, s32 x, s32 y);
extern void func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 f);

s32 normal_TransMenuCursorBobToCell_514ad0(Obj *p, void *w, s32 dx, s32 dy)
{
    s32 ox;
    s32 oy;
    f32 t;

    func_28B630(&D_00484780, 0.078539819f);
    t = 6.0f * func_128FD0(D_00484780);
    func_28ECD0(p, &ox, &oy, (s32)(t + dx), (s32)(p->f12 + (t + dy)));
    func_290F50(w, 0x7556, ox, oy, 0, 0.25f);
    return 1;
}
