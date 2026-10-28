/* rg-override: replaces game/src/main/gs/GsPktSetXYZfVec_13efe0.c sha256 e9cc69fe9d588c8cb1b238ae4086946d0ca75eb05b754e5d1c6e261c33037d29
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* XYZ2 (reg 5) from a float vector: vftoi4.xy (12.4 fixed point) and
   vftoi0.z on vf10, then packed like GsPktSetXYZVecI. */
void GsPktSetXYZfVec_13efe0(void *pkt, const f32 *v)
{ RG_VU0_FRAME;
    s32 tmp[4] __attribute__((aligned(16)));
    u8 *p;
    s32 xf, yf;

    rg_vu0_lqc2(10, (const char *)v);   /* lqc2     vf10, 0x0($5) */
    rg_vu0_ftoi(4, RG_XY, 10, 10);      /* vftoi4.xy vf10, vf10 */
    rg_vu0_ftoi(0, RG_Z, 10, 10);       /* vftoi0.z vf10, vf10 */
    rg_vu0_sqc2(10, (char *)tmp);       /* sqc2     vf10, 0x0($3) */

    xf = (s32)((u32)tmp[0] + *(u32 *)((u8 *)pkt + 0x120));
    yf = (s32)((u32)tmp[1] + *(u32 *)((u8 *)pkt + 0x124));
    p = *(u8 **)((u8 *)pkt + 0xF4);
    *(u64 *)(p + 0x0) = ((u64)(u32)tmp[2] << 32) | (u64)(s64)xf | ((u64)(s64)yf << 16);
    *(u64 *)(p + 0x8) = 5;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
