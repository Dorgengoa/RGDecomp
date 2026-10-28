#include "types.h"

/* Hand-written PS2 SDK syscall wrapper -- verbatim transcription (retail
   is `addiu $3,$0,0x7B / syscall 0 / jr $31 / nop`; mwcc auto-appends the
   trailing jr/nop, see MODEL.md). */

void _ExecOSD(void)
{
    asm volatile {
        addiu $3, $0, 0x7B
        syscall 0
    }
}
