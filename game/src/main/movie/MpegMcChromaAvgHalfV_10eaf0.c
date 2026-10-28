#include "types.h"

/* Hand-written byte-shuffle/average loop family member. */

void MpegMcChromaAvgHalfV_10eaf0(void)
{
    asm volatile {
        .set noreorder
        lw    $14, 0x0($4)
        lw    $5, 0x14($4)
        lw    $6, 0x18($4)
        lw    $12, 0x10($4)
        lw    $13, 0x4($4)
        pnor  $25, $0, $0
        psrlh $25, $25, 15
        addiu $11, $0, 0x1
        sll   $24, $12, 1
        mtsab $13, 0x0
    L0010EB18:
        lw    $7, 0x8($4)
        ld    $8, 0x0($5)
        ld    $9, 0x0($6)
        pcpyld $8, $9, $8
        qfsrv $8, $8, $8
        ori   $11, $11, 0x8000
        beqz  $7, L0010EB8C
        pextlb $15, $0, $8
    L0010EB38:
        addu  $5, $5, $12
        addu  $6, $6, $12
        ld    $8, 0x0($5)
        ld    $9, 0x0($6)
        pcpyld $8, $9, $8
        qfsrv $8, $8, $8
        pextlb $10, $0, $8
        addi  $7, $7, -0x1
        paddh $9, $10, $15
        por   $15, $10, $0
        paddh $10, $9, $25
        psrlh $10, $10, 1
        lq    $8, 0x0($14)
        paddh $10, $10, $8
        pcgth $9, $10, $0
        psrlh $9, $9, 15
        paddh $10, $10, $9
        psrlh $10, $10, 1
        sq    $10, 0x0($14)
        bgtz  $7, L0010EB38
        addu  $14, $14, $24
    L0010EB8C:
        psrah $10, $11, 15
        addiu $5, $5, 0x140
        lw    $7, 0xC($4)
        addiu $6, $6, 0x140
        and   $10, $10, $7
        bnez  $10, L0010EB38
        andi  $11, $11, 0x7FFF
        lw    $14, 0x0($4)
        lw    $5, 0x14($4)
        lw    $6, 0x18($4)
        addiu $14, $14, 0x80
        addiu $5, $5, 0x40
        addiu $6, $6, 0x40
        andi  $10, $11, 0x1
        bnez  $10, L0010EB18
        andi  $11, $11, 0xFFFE
    }
}
