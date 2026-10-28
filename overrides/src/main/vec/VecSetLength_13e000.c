/* rg-override: replaces game/src/main/vec/VecSetLength_13e000.c sha256 21b87dbf1bcb9a24391e008005f2d53a40a71932fe5680ea31070ceeee15baf0
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void VecNormalize_13bd90(void *d, const void *s);

/* d = normalize(s) * len (w = 0 * len). */
void VecSetLength_13e000(void *d, const void *s, f32 len)
{ RG_VU0_FRAME;
    u8 t[16];                                               /* sp+0x30 */
    VecNormalize_13bd90(t, s);                              /* jal VecNormalize; $4 = sp+0x30, $5 = s */
    rg_vu0_lqc2(4, t);                                      /* lqc2 vf4, 0($3=sp+0x30) */
    rg_vu0_mfc1(8, len);                                    /* mfc1 $8, $f20 */
    rg_vu0_qmtc2(8, 5);                                     /* qmtc2 $8, vf5 */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_X);        /* vmulx.xyzw vf6, vf4, vf5x */
    rg_vu0_sqc2(6, d);                                      /* sqc2 vf6, 0($16) */
}
