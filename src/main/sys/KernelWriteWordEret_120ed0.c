#include "types.h"

/* Naked `asm void` (lever 6). Ends in `eret` (exception return), not
   `jr $31` -- must be written explicitly regardless. */

asm void KernelWriteWordEret_120ed0(void)
{
    .set noreorder;
    mfc0  $3, $12;
    lui   $2, (0x10000 >> 16);
    and   $3, $3, $2;
    beqz  $3, L00120F0C;
    lui   $6, (0x10000 >> 16);
    nop;
L00120EE8:
    di;
    sync.p;
    mfc0  $2, $12;
    and   $2, $2, $6;
    nop;
    nop;
    nop;
    bnez  $2, L00120EE8;
    nop;
L00120F0C:
    mfc0  $2, $12;
    sync.p;
    ori   $2, $2, 0x6;
    xori  $2, $2, 0x2;
    or    $2, $2, $3;
    mtc0  $2, $12;
    sync.p;
    sw    $5, 0x0($4);
    mtc0  $31, $30;
    sync.p;
    eret;
}
