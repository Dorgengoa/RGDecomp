#include "types.h"
#include "vec.h"

/* Length of a Vec4's xyz. The three squares are summed with two `vmr32`
   rotations rather than the `vaddy/vaddz` chain the quaternion dot product
   uses, and the square root comes back through VU0's Q register -- `vsqrt`,
   `vwaitq`, then `cfc2` out of $vi22 and `mtc1` into the float return.
   There is no path from Q to an FPR that does not go through a GPR. */

f32 VecLength_13d4a0(const Vec4 *pv)
{
    f32 r;

    asm volatile {
        lqc2     vf4, 0(pv)
        vmul.xyz vf4, vf4, vf4
        vmr32.xy vf5, vf4
        vmr32.x  vf6, vf5
        vadd.x   vf7, vf4, vf5
        vadd.x   vf5, vf6, vf7
        vsqrt    Q, vf5x
        vwaitq
        cfc2.ni  $2, $vi22
        mtc1     $2, r
    }
    return r;
}
