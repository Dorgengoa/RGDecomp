#include "types.h"

/* Hand-written byte-shuffle/average loop family member. */

void MpegMcLumaAvgHalfV_10ea10(void)
{
    asm volatile {
        .set noreorder
        lw    $14, 0x0($4)
        lw    $5, 0x14($4)
        lw    $6, 0x18($4)
        lw    $12, 0x10($4)
        lw    $13, 0x4($4)
        lw    $7, 0x8($4)
        pnor  $25, $0, $0
        psrlh $25, $25, 15
        lq    $8, 0x0($5)
        lq    $9, 0x0($6)
        mtsab $13, 0x0
        qfsrv $10, $9, $8
        sll   $24, $12, 1
        pextlb $8, $0, $10
        addiu $11, $0, -0x1
        beqz  $7, L0010EACC
        pextub $9, $0, $10
    L0010EA54:
        addu  $5, $5, $12
        addu  $6, $6, $12
        lq    $10, 0x0($5)
        lq    $15, 0x0($6)
        qfsrv $2, $15, $10
        pextlb $10, $0, $2
        addi  $7, $7, -0x1
        pextub $15, $0, $2
        paddh $2, $8, $10
        paddh $3, $9, $15
        por   $8, $10, $0
        por   $9, $15, $0
        paddh $2, $2, $25
        paddh $3, $3, $25
        psrlh $2, $2, 1
        psrlh $3, $3, 1
        lq    $10, 0x0($14)
        lq    $15, 0x10($14)
        paddh $2, $2, $10
        paddh $3, $3, $15
        paddh $10, $2, $25
        psrlh $2, $10, 1
        pcgth $10, $3, $0
        psrlh $10, $10, 15
        paddh $10, $3, $10
        psrlh $3, $10, 1
        sq    $2, 0x0($14)
        sq    $3, 0x10($14)
        bgtz  $7, L0010EA54
        addu  $14, $14, $24
    L0010EACC:
        addiu $5, $5, 0x80
        addiu $6, $6, 0x80
        lw    $7, 0xC($4)
        and   $10, $11, $7
        bnez  $10, L0010EA54
        daddu $11, $0, $0
    }
}
