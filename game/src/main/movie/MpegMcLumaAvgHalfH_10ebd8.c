#include "types.h"

/* UNREGISTERED symbol -- see MpegMcLumaCopy_10e2c8.c note (same park). */

asm void MpegMcLumaAvgHalfH_10ebd8(void)
{
    .set noreorder;
    lw    $14, 0x0($4);
    lw    $5, 0x14($4);
    lw    $6, 0x18($4);
    lw    $9, 0x10($4);
    lw    $13, 0x4($4);
    lw    $7, 0x8($4);
    pnor  $25, $0, $0;
    psrlh $25, $25, 15;
    addiu $24, $0, 0x1;
    sll   $8, $9, 1;
    addiu $11, $0, -0x1;
L0010EC04:
    lq    $10, 0x0($5);
    lq    $15, 0x0($6);
    mtsab $13, 0x0;
    qfsrv $2, $15, $10;
    qfsrv $3, $10, $15;
    pextlb $10, $0, $2;
    addi  $7, $7, -0x1;
    pextub $15, $0, $2;
    mtsab $24, 0x0;
    qfsrv $3, $3, $2;
    pextlb $2, $0, $3;
    pextub $3, $0, $3;
    paddh $10, $10, $2;
    paddh $15, $15, $3;
    paddh $2, $10, $25;
    paddh $3, $15, $25;
    psrlh $2, $2, 1;
    psrlh $3, $3, 1;
    lq    $10, 0x0($14);
    lq    $15, 0x10($14);
    paddh $2, $2, $10;
    paddh $3, $3, $15;
    paddh $10, $2, $25;
    psrlh $2, $10, 1;
    pcgth $10, $3, $0;
    psrlh $10, $10, 15;
    paddh $10, $3, $10;
    psrlh $3, $10, 1;
    sq    $2, 0x0($14);
    sq    $3, 0x10($14);
    addu  $5, $5, $9;
    addu  $6, $6, $9;
    bgtz  $7, L0010EC04;
    addu  $14, $14, $8;
    addiu $5, $5, 0x80;
    addiu $6, $6, 0x80;
    lw    $7, 0xC($4);
    and   $12, $11, $7;
    bnez  $12, L0010EC04;
    daddu $11, $0, $0;
    jr    $31;
    nop;
    nop;
}
