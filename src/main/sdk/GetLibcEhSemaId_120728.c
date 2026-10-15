#include "types.h"

/* Retail stages the address in $3 and the loaded value in $2 (distinct
   registers) plus a trailing nop; every compiler-plausible C shape measured
   collapses both into one register and drops the nop. Transcribed verbatim
   as naked asm (plain shifted/masked literal, not %hi/%lo -- naked mode's
   assembler rejects %hi/%lo syntax) to guarantee the byte match. */

asm void GetLibcEhSemaId_120728(void)
{
    .set noreorder;
    lui   $3, (0x00446934 >> 16);
    jr    $31;
    lw    $2, (0x00446934 & 0xFFFF)($3);
    nop;
}
