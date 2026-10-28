#include "types.h"

/* Hand-written byte-shuffle/average loop family member. */

void MpegMcLumaAvg_10e8c0(void)
{
    asm volatile {
        .set noreorder
        lw    $14, 0x0($4)
        lw    $5, 0x14($4)
        lw    $6, 0x18($4)
        lw    $9, 0x10($4)
        lw    $13, 0x4($4)
        lw    $7, 0x8($4)
        sll   $8, $9, 1
        addiu $11, $0, -0x1
        mtsab $13, 0x0
    L0010E8E4:
        lq    $10, 0x0($5)
        lq    $15, 0x0($6)
        qfsrv $2, $15, $10
        pextlb $10, $0, $2
        pextub $15, $0, $2
        lq    $2, 0x0($14)
        lq    $3, 0x10($14)
        paddh $2, $2, $10
        paddh $3, $3, $15
        pnor  $25, $0, $0
        psrlh $25, $25, 15
        paddh $10, $2, $25
        psrlh $2, $10, 1
        paddh $10, $3, $25
        psrlh $3, $10, 1
        sq    $2, 0x0($14)
        sq    $3, 0x10($14)
        addi  $7, $7, -0x1
        addu  $5, $5, $9
        addu  $14, $14, $8
        bgtz  $7, L0010E8E4
        addu  $6, $6, $9
        addiu $5, $5, 0x80
        addiu $6, $6, 0x80
        lw    $7, 0xC($4)
        and   $12, $11, $7
        bnez  $12, L0010E8E4
        daddu $11, $0, $0
    }
}
