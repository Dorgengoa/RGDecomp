/* CameraChaseSetEyeYawThunk_161240 -- shape-identical to merged KernelExitThunk_120d18 (1 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 0 immediate(s) substituted:
     KernelExit_120d18 -> CameraSetEyeYaw_176e10
   Found by build/zz/s23_xclone.py. */
#include "types.h"

extern void CameraSetEyeYaw_176e10(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CameraChaseSetEyeYawThunk_161240(s32 p0)
{
    CameraSetEyeYaw_176e10(p0);
}
