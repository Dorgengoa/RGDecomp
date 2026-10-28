/* rg-override: replaces game/src/main/gs/GsPktSetRGBAQVec_13edd0.c sha256 62ea88d5adbf5b01e49e4f471ef9eb2d75cd08618aec67f9452e0dd9b7f55b24
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* RGBAQ (reg 1) from a float colour vector: lqc2 vf10 / vftoi0.xyzw /
   sqc2 to a stack qword, then the four ints are packed like GsPktSetRGBAQ. */
void GsPktSetRGBAQVec_13edd0(void *pkt, const f32 *rgba)
{ RG_VU0_FRAME;
    s32 tmp[4] __attribute__((aligned(16)));
    u8 *p;
    u64 v;

    rg_vu0_lqc2(10, (const char *)rgba);   /* lqc2     vf10, 0x0($5) */
    rg_vu0_ftoi(0, RG_XYZW, 10, 10);       /* vftoi0.xyzw vf10, vf10 */
    rg_vu0_sqc2(10, (char *)tmp);          /* sqc2     vf10, 0x0($3) */

    v = (u64)(s64)tmp[0]
      | ((u64)(s64)tmp[1] << 8)
      | ((u64)(s64)tmp[2] << 16)
      | ((u64)(s64)tmp[3] << 24);
    v |= (u64)*(u32 *)((u8 *)pkt + 0x110) << 32;
    p = *(u8 **)((u8 *)pkt + 0xF4);
    *(u64 *)(p + 0x0) = v;
    *(u64 *)(p + 0x8) = 1;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
