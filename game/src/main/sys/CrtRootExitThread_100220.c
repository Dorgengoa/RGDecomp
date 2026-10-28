#include "types.h"

/* Hand-written syscall stub with NO jr $31 -- retail falls through into
   whatever follows in the image instead of returning. Likely part of the
   boot sequence near `entry`, not an ordinary callable function. */

asm void CrtRootExitThread_100220(void)
{
    .set noreorder;
    addiu $3, $0, 0x23;
    syscall 0;
    nop;
    nop;
}
