#include "types.h"

/* Hand-written byte-shuffle/average loop family member (sibling of
   MpegMcChromaCopy_10e340/MpegMcChromaHalfV_10e490). Pure raw-register asm. */

void MpegMcLumaHalfH_10e560(void)
{
    asm volatile {
        .set noreorder
        lw    $14, 0x0($4)
        lw    $5, 0x14($4)
        lw    $6, 0x18($4)
        lw    $9, 0x10($4)
        lw    $13, 0x4($4)
        lw    $7, 0x8($4)
        pnor  $25, $0, $0
        psrlh $25, $25, 15
        addiu $24, $0, 0x1
        sll   $8, $9, 1
        addiu $11, $0, -0x1
    L0010E58C:
        lq    $10, 0x0($5)
        lq    $15, 0x0($6)
        mtsab $13, 0x0
        qfsrv $2, $15, $10
        qfsrv $3, $10, $15
        pextlb $10, $0, $2
        addi  $7, $7, -0x1
        pextub $15, $0, $2
        mtsab $24, 0x0
        qfsrv $3, $3, $2
        pextlb $2, $0, $3
        pextub $3, $0, $3
        paddh $10, $10, $2
        paddh $15, $15, $3
        paddh $2, $10, $25
        paddh $3, $15, $25
        psrlh $2, $2, 1
        psrlh $3, $3, 1
        sq    $2, 0x0($14)
        sq    $3, 0x10($14)
        addu  $5, $5, $9
        addu  $6, $6, $9
        bgtz  $7, L0010E58C
        addu  $14, $14, $8
        addiu $5, $5, 0x80
        addiu $6, $6, 0x80
        lw    $7, 0xC($4)
        and   $12, $11, $7
        bnez  $12, L0010E58C
        daddu $11, $0, $0
    }
}
