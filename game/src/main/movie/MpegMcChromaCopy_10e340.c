#include "types.h"

/* Hand-written: nested double loop doing a byte/word shuffle+SIMD copy
   (qfsrv/pcpyld/pextlb). Pure raw-register asm, no external symbols.
   Registered size 0x94 = 37 words; retail's listing shows one further
   dead `nop` past that (belongs to the next symbol, lever 4) -- omitted
   here along with the final `jr $31`/delay nop (lever 1, mwcc supplies
   them). */

void MpegMcChromaCopy_10e340(void)
{
    asm volatile {
        .set noreorder
        lw    $5, 0x0($4)
        lw    $6, 0x14($4)
        lw    $7, 0x18($4)
        lw    $13, 0x10($4)
        lw    $12, 0x4($4)
        sll   $11, $13, 1
        mtsab $12, 0x0
        addiu $24, $0, -0x1
    L0010E360:
        lw    $15, 0x8($4)
        addiu $25, $0, -0x1
    L0010E368:
        ld    $8, 0x0($6)
        ld    $9, 0x0($7)
        pcpyld $8, $9, $8
        qfsrv  $9, $8, $8
        pextlb $8, $0, $9
        sq    $8, 0x0($5)
        addi  $15, $15, -0x1
        addu  $6, $6, $13
        addu  $5, $5, $11
        bgtz  $15, L0010E368
        addu  $7, $7, $13
        addiu $6, $6, 0x140
        addiu $7, $7, 0x140
        lw    $15, 0xC($4)
        and   $10, $25, $15
        bnez  $10, L0010E368
        daddu $25, $0, $0
        lw    $5, 0x0($4)
        lw    $6, 0x14($4)
        lw    $7, 0x18($4)
        addiu $5, $5, 0x80
        addiu $6, $6, 0x40
        addiu $7, $7, 0x40
        bnez  $24, L0010E360
        daddu $24, $0, $0
    }
}
