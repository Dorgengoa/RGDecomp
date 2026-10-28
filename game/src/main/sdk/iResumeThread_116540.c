#include "types.h"

/* Handwritten function (asm/matchings/main/iResumeThread_116540.s: "Handwritten function").
   PS2 SDK syscall trampoline (addiu $3,N; syscall 0; return) -- transcribed
   verbatim. Trailing jr $31/nop omitted per the lever in MODEL.md. */

void iResumeThread_116540(void)
{
    asm volatile {
        .set noreorder
        addiu      $3, $0, -0x3A
        syscall    0
    }
}
