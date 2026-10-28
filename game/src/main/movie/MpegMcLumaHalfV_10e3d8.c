#include "types.h"

/* UNREGISTERED symbol -- see MpegMcLumaCopy_10e2c8.c note (same park). */

asm void MpegMcLumaHalfV_10e3d8(void)
{
    .set noreorder;
    lw    $14, 0x0($4);
    lw    $5, 0x14($4);
    lw    $6, 0x18($4);
    lw    $24, 0x10($4);
    lw    $13, 0x4($4);
    lw    $7, 0x8($4);
    pnor  $25, $0, $0;
    psrlh $25, $25, 15;
    lq    $8, 0x0($5);
    sll   $12, $24, 1;
    lq    $9, 0x0($6);
    mtsab $13, 0x0;
    qfsrv $10, $9, $8;
    pextlb $8, $0, $10;
    addiu $11, $0, -0x1;
    beqz  $7, L0010E46C;
    pextub $9, $0, $10;
L0010E41C:
    addu  $5, $5, $24;
    addu  $6, $6, $24;
    lq    $10, 0x0($5);
    lq    $15, 0x0($6);
    qfsrv $2, $15, $10;
    pextlb $10, $0, $2;
    addi  $7, $7, -0x1;
    pextub $15, $0, $2;
    paddh $2, $8, $10;
    paddh $3, $9, $15;
    por   $8, $10, $0;
    por   $9, $15, $0;
    paddh $2, $2, $25;
    paddh $3, $3, $25;
    psrlh $2, $2, 1;
    psrlh $3, $3, 1;
    sq    $2, 0x0($14);
    sq    $3, 0x10($14);
    bgtz  $7, L0010E41C;
    addu  $14, $14, $12;
L0010E46C:
    addiu $5, $5, 0x80;
    addiu $6, $6, 0x80;
    lw    $7, 0xC($4);
    and   $10, $11, $7;
    bnez  $10, L0010E41C;
    daddu $11, $0, $0;
    jr    $31;
    nop;
    nop;
}
