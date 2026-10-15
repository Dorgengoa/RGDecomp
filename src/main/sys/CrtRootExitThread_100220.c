#include "types.h"

/* Approved startup assembly exception (2026-10-14): startup ExitThread stub, syscall number 0x23.
 * Its address is passed in t0 to startup syscall 0x3c. Normal thread exit
 * does not continue here. If resumed at EPC+4, two nops lead into the
 * distinct DoubleGreaterEqual_100230; this is not evidence of intentional fall-through.
 * Retains the original four instructions; NOT a C decompilation.
 * See build/libdeasm/100220/NOTES.md. */
asm void CrtRootExitThread_100220(void)
{
    .set noreorder;
    addiu $3, $0, 0x23;
    syscall 0;
    nop;
    nop;
}
