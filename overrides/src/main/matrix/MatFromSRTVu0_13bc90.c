/* rg-override: replaces game/src/main/matrix/MatFromSRTVu0_13bc90.c sha256 dc7c3144e438d5d7735c2d1548e23bac1cc278fd6dff800b0110f469580044a2
 * why: asm body (asmexclude); C port on the VU0 model, `vcallms 0x0` runs the retail VU0
 * microprogram (uploaded by GfxSysInit) on the shared register file (src/ps2/vu0_micro.c);
 * RG_VU0_LOCAL (RG_VU0_MODE local/native): the program as native C instead */
#include "types.h"

/* out = scale(*s) * rot(*r Euler angles) + translation(*t), as rows of a
   4x4 (vf4..vf7 from the microprogram at VU0 micro address 0). */
#if RG_VU0_IS_LOCAL
/* native: the microprogram as C (src/sce/vu0/vu0_srt.c, docs/NATIVE-CPU.md) */
void MatFromSRTVu0_13bc90(void *out, void *s, void *r, void *t)
{ RG_VU0_FRAME;
    rg_vf vs, vr, vt, m[4];
    __builtin_memcpy(&vs, s, 16); /* lqc2 $vf1, 0x0($5) */
    __builtin_memcpy(&vr, r, 16); /* lqc2 $vf2, 0x0($6) */
    __builtin_memcpy(&vt, t, 16); /* lqc2 $vf3, 0x0($7) */
    rg_vu0_srt(m, &vs, &vr, &vt); /* vcallms 0x0; vnop */
    __builtin_memcpy(out, m, 64); /* sqc2 $vf4..$vf7, 0x0..0x30($4) */
}
#else
void MatFromSRTVu0_13bc90(void *out, void *s, void *r, void *t)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(1, (char *)s); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)r); /* lqc2       $vf2, 0x0($6) */
    rg_vu0_lqc2(3, (char *)t); /* lqc2       $vf3, 0x0($7) */
    rg_vu0_vcallms(0x0);       /* vcallms    0x0 */
    rg_vu0_waitq();            /* vnop (waits for the program on hardware) */
    rg_vu0_sqc2(4, (char *)out); /* sqc2       $vf4, 0x0($4) */
    rg_vu0_sqc2(5, (char *)out + 0x10); /* sqc2       $vf5, 0x10($4) */
    rg_vu0_sqc2(6, (char *)out + 0x20); /* sqc2       $vf6, 0x20($4) */
    rg_vu0_sqc2(7, (char *)out + 0x30); /* sqc2      $vf7, 0x30($4) */
}
#endif
