/* rg-override: replaces game/src/main/matrix/MtxRotZ_13cdb0.c sha256 a5beca8af53cff8c38697b199d5f582529cd49530efda66358c607022f46cf68
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);

/* m = rotation about Z by a (identity built with vmr32 from vf0). */
void MtxRotZ_13cdb0(void *m, f32 a)
{ RG_VU0_FRAME;
    char *p = (char *)m;
    f32 c, s;
    rg_vu0_mr32(RG_XYZW, 1, 0);                             /* vmr32.xyzw vf1, vf0 */
    rg_vu0_mr32(RG_XYZW, 2, 1);                             /* vmr32.xyzw vf2, vf1 */
    rg_vu0_mr32(RG_XYZW, 3, 2);                             /* vmr32.xyzw vf3, vf2 */
    rg_vu0_sqc2(0, p + 0x30);                               /* sqc2 vf0, 0x30($16) */
    rg_vu0_sqc2(1, p + 0x20);                               /* sqc2 vf1, 0x20($16) */
    rg_vu0_sqc2(2, p + 0x10);                               /* sqc2 vf2, 0x10($16) */
    rg_vu0_sqc2(3, p);                                      /* sqc2 vf3, 0($16) (jal slot) */
    c = Cosf_128d30(a);                                     /* jal Cosf_128d30 */
    *(f32 *)(p + 0x14) = c;                                 /* swc1 $f0, 0x14($16) */
    *(f32 *)(p + 0x0) = c;                                 /* swc1 $f0, 0x0($16) (jal slot) */
    s = Sinf_128fd0(a);                                     /* jal Sinf_128fd0 */
    *(f32 *)(p + 0x4) = s;                                 /* swc1 $f0, 0x4($16) */
    *(f32 *)(p + 0x10) = -s;                                /* neg.s; swc1 $f0, 0x10($16) */
}
