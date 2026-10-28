#include "types.h"

/* Hand-written PS2 SDK syscall wrapper -- verbatim transcription. */

void _iWakeupThread(void)
{
    asm volatile {
        addiu $3, $0, -0x34
        syscall 0
    }
}
