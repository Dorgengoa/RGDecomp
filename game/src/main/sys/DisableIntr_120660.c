#include "types.h"

/* Hand-written: busy-wait for interrupts to be re-enabled (if they were
   disabled), disabling them again around the check. Two exits: the FIRST
   `jr $31` is a REAL mid-function return (inside the wait loop's taken
   branch) so it must be written explicitly; only the LAST one (the
   function's true fall-off end) is omitted per the usual lever, letting
   mwcc's auto-appended jr/delay pick up the trailing `daddu $2,$4,$0`. */

s32 DisableIntr_120660(void)
{
    asm volatile {
        .set noreorder
        mfc0  $3, $12
        lui   $2, 0x1
        and   $3, $3, $2
        beqz  $3, L001206A4
        sltu  $4, $0, $3
        nop
    L00120678:
        di
        sync.p
        mfc0  $2, $12
        lui   $3, 0x1
        and   $2, $2, $3
        nop
        nop
        bnez  $2, L00120678
        nop
        jr    $31
        daddu $2, $4, $0
    L001206A4:
        daddu $4, $0, $0
        daddu $2, $4, $0
    }
}
