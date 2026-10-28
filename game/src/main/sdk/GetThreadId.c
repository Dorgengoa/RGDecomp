#include "types.h"

/* Hand-written PS2 SDK syscall wrapper -- verbatim transcription. */

void GetThreadId(void)
{
    asm volatile {
        addiu $3, $0, 0x2F
        syscall 0
    }
}
