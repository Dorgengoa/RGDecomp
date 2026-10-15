#include "types.h"
/* normal 0x00515CD0 -- widget tint/alpha pass.  No callee-saved frame at all,
 * so both gp pointers are RE-READ at every call site rather than held. */
extern void *D_004846E8;
extern void *D_004846EC;
extern f32   D_0047DA08;
extern f32   D_0047DA18;

extern void func_291110(void *a, u16 id, s32 c, s32 d);
extern void func_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern void func_290F50(void *a, u16 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_TransMenuHeaderFadeOut_515cd0(void)
{
    func_291110(D_004846E8, 0x754C, 0, 1);
    func_291110(D_004846E8, 0x754B, 0, 1);
    func_290690(D_004846EC, 0x84D1, 0.0f, D_0047DA08, 1.0f);
    func_290690(D_004846E8, 0x7532, 0.0f, D_0047DA08, 1.0f);
    func_290F50(D_004846E8, 0x7534, -0x30, -0xF, 0, D_0047DA18);
    func_290690(D_004846E8, 0x7534, 0.0f, D_0047DA08, -1.0f);
    func_290690(D_004846E8, 0x7533, 0.0f, D_0047DA08, -1.0f);
    return 1;
}
