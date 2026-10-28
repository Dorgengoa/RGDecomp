#include "types.h"

/* Handwritten function (asm/matchings/main/iReleaseAlarm_116390.s: "Handwritten function").
   PS2 SDK syscall trampoline (addiu $3,N; syscall 0; return) -- transcribed
   verbatim. Trailing jr $31/nop omitted per the lever in MODEL.md. */

void iReleaseAlarm_116390(void)
{
    asm volatile {
        .set noreorder
        addiu      $3, $0, -0xFF
        syscall    0
    }
}
