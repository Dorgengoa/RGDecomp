/* rg-override: replaces game/src/main/gs/GsPktSetXYZf_13f060.c sha256 f6d1d2121c6cd6702bb381d4b1b5d62da14c2ac48e847e29a5f8c34a40257895
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* XYZ2 (reg 5) from three floats: a zeroed stack qword (x, y, z, 0) goes
   through vf10 (vftoi4.xy, vftoi0.z) and is packed like GsPktSetXYZVecI. */
void GsPktSetXYZf_13f060(void *pkt, f32 x, f32 y, f32 z)
{ RG_VU0_FRAME;
    f32 in[4] __attribute__((aligned(16)));
    s32 tmp[4] __attribute__((aligned(16)));
    u8 *p;
    s32 xf, yf;

    __builtin_memset(in, 0, sizeof(in)); /* the sb $0 clear loop */
    in[0] = x;
    in[1] = y;
    in[2] = z;
    rg_vu0_lqc2(10, (const char *)in);  /* lqc2     vf10, 0x0($5) */
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
