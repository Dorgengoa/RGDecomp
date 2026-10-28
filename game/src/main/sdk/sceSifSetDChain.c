#include "types.h"

/* Handwritten function (asm/matchings/main/sceSifSetDChain.s: "Handwritten function").
   PS2 SDK syscall trampoline (addiu $3,N; syscall 0; return) -- transcribed
   verbatim. Trailing jr $31/nop omitted per the lever in MODEL.md. */

void sceSifSetDChain(void)
{
    asm volatile {
        .set noreorder
        addiu      $3, $0, 0x78
        syscall    0
    }
}
