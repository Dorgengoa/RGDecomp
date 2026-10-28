#include "types.h"

/* Handwritten function (asm/matchings/main/iPutTLBEntry_120008.s: "Handwritten function").
   PS2 SDK syscall trampoline (addiu $3,N; syscall 0; return) -- transcribed
   verbatim. Trailing jr $31/nop omitted per the lever in MODEL.md. */

void iPutTLBEntry_120008(void)
{
    asm volatile {
        .set noreorder
        addiu      $3, $0, -0x55
        syscall    0
    }
}
