#include "types.h"
#include "vec.h"

/* Build the matrix, then overwrite its last row with VU0's hard-wired
   `vf0` -- (0,0,0,1). The constant never touches memory or a GPR, which is
   why this needs a one-instruction asm block rather than a `Vec4` literal. */

extern void MatFromQuat_13c440(Mtx4 *m);

void MatFromQuatFull_13c4c0(Mtx4 *m)
{
    MatFromQuat_13c440(m);
    asm volatile {
        sqc2 vf0, 0x30(m)
    }
}
