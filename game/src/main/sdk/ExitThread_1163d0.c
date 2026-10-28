#include "types.h"

/* Handwritten function (asm/matchings/main/ExitThread_1163d0.s: "Handwritten function").
   PS2 SDK syscall trampoline (addiu $3,N; syscall 0; return) -- transcribed
   verbatim. Trailing jr $31/nop omitted per the lever in MODEL.md. */

void ExitThread_1163d0(void)
{
    asm volatile {
        .set noreorder
        addiu      $3, $0, 0x23
        syscall    0
    }
}
