/* rgp:protos */
#define RGP_SELF_sceVu0UnitMatrix 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* The identity matrix, built without touching memory for the constants:
   `vf0` is VU0's hard-wired (0,0,0,1), so `vf0 - vf0` is zero and adding
   `vf0`'s w back gives (0,0,0,1). Three `vmr32` rotations then produce
   (0,0,1,0), (0,1,0,0), (1,0,0,0) -- which is why the rows are STORED in
   descending address order, 0x30 first and 0x00 last.

   libvu0 is inline assembly in the SDK and the content says so: no compiler
   derives four rows from a rotate chain. */

void sceVu0UnitMatrix(Mtx4 *m)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_fmac(RG_VSUB, RG_XYZW, 4, 0, 0, RG_BC_NONE); /* vsub.xyzw  vf4, vf0, vf0 */
rg_vu0_fmac(RG_VADD, RG_W, 4, 4, 0, RG_BC_NONE); /* vadd.w     vf4, vf4, vf0 */
rg_vu0_mr32(RG_XYZW, 5, 4); /* vmr32.xyzw vf5, vf4 */
rg_vu0_mr32(RG_XYZW, 6, 5); /* vmr32.xyzw vf6, vf5 */
rg_vu0_mr32(RG_XYZW, 7, 6); /* vmr32.xyzw vf7, vf6 */
rg_vu0_sqc2(4, (char *)(m) + 0x30); /* sqc2       vf4, 0x30(m) */
rg_vu0_sqc2(5, (char *)(m) + 0x20); /* sqc2       vf5, 0x20(m) */
rg_vu0_sqc2(6, (char *)(m) + 0x10); /* sqc2       vf6, 0x10(m) */
rg_vu0_sqc2(7, (char *)(m)); /* sqc2       vf7, 0x0(m) */
}
}
