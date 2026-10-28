#include "types.h"

/* Handwritten function (asm/matchings/main/RemoveSbusIntcHandler_116230.s: "Handwritten function").
   PS2 SDK syscall trampoline (addiu $3,N; syscall 0; return) -- transcribed
   verbatim. Trailing jr $31/nop omitted per the lever in MODEL.md. */

void RemoveSbusIntcHandler_116230(void)
{
    asm volatile {
        .set noreorder
        addiu      $3, $0, 0xB
        syscall    0
    }
}
