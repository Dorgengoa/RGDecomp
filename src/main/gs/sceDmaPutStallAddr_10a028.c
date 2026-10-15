#include "types.h"

/* Genuinely hand-written: mwcc's own compiled equivalent for this constant
   address folds to a 4-word lui+lw/sw-with-signed-offset (measured), but
   retail spells out a full lui/ori address build (6 words, trailing nop) --
   the compiler-plausible C shape cannot reach it. Transcribed verbatim. */

asm void sceDmaPutStallAddr_10a028(void)
{
    .set noreorder;
    lui   $3, 0x1000;
    ori   $3, $3, 0xE060;
    lw    $2, 0x0($3);
    jr    $31;
    sw    $4, 0x0($3);
    nop;
}
