/* rgp:protos */
#define RGP_SELF_MatFromQuatFull_13c4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Build the matrix, then overwrite its last row with VU0's hard-wired
   `vf0` -- (0,0,0,1). The constant never touches memory or a GPR, which is
   why this needs a one-instruction asm block rather than a `Vec4` literal. */

/*rgp*/

void MatFromQuatFull_13c4c0(Mtx4 *m, void *rgp_a1)
{ RG_VU0_FRAME;
    MatFromQuat_13c440(m, (void *)rgp_a1);
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_sqc2(0, (char *)(m) + 0x30); /* sqc2 vf0, 0x30(m) */
}
}
