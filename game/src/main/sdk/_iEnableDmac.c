#include "types.h"

/* Hand-written PS2 SDK syscall wrapper -- verbatim transcription. */

void _iEnableDmac(void)
{
    asm volatile {
        addiu $3, $0, -0x1C
        syscall 0
    }
}
