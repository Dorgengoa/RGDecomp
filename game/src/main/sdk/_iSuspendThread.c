#include "types.h"

/* Hand-written PS2 SDK syscall wrapper -- verbatim transcription. */

void _iSuspendThread(void)
{
    asm volatile {
        addiu $3, $0, -0x38
        syscall 0
    }
}
