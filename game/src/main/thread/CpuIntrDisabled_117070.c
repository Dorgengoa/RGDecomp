#include "types.h"

/* COP0 status-register probe -- reads $12 (Status), flips bit0, ANDs back
   to bit0. Delay slot of retail's `jr $31` is the ANDI itself (independent
   of the branch), so we omit `jr $31` and let mwcc's auto-epilogue absorb
   the trailing andi into the delay slot -- same trick as the syscall
   stubs. */

s32 CpuIntrDisabled_117070(void)
{
    asm volatile {
        mfc0  $2, $12
        xori  $2, $2, 0x1
        andi  $2, $2, 0x1
    }
}
