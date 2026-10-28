#include "types.h"

/* Hand-written PS2 SDK syscall wrapper -- verbatim transcription. */

void _iEnableIntc(void)
{
    asm volatile {
        addiu $3, $0, -0x1A
        syscall 0
    }
}
