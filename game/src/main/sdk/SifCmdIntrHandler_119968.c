#include "types.h"

extern void isceSifSetDChain(void);

/* Naked `asm void` (lever 6). D_00486918 hi/lo hardcoded per lever 5. */

asm void SifCmdIntrHandler_119968(void)
{
    .set noreorder;
    addiu $29, $29, -0xA0;
    lui   $3, 0x48;
    sd    $17, 0x80($29);
    sd    $31, 0x90($29);
    addiu $17, $3, 0x6918;
    sd    $16, 0x70($29);
    lw    $7, 0x6918($3);
    lbu   $2, 0x0($7);
    andi  $5, $2, 0xFF;
    beqz  $5, L00119A9C;
    daddu $2, $0, $0;
    addiu $2, $5, 0xF;
    addiu $3, $0, -0x1;
    addiu $4, $5, 0x1E;
    slt   $3, $3, $2;
    movn  $4, $2, $3;
    daddu $6, $7, $0;
    sra   $5, $4, 4;
    sb    $0, 0x0($7);
    blez  $5, L001199DC;
    daddu $4, $5, $0;
    daddu $3, $29, $0;
L001199C0:
    lq    $2, 0x0($6);
    addiu $4, $4, -0x1;
    addiu $6, $6, 0x10;
    sq    $2, 0x0($3);
    addiu $3, $3, 0x10;
    bnez  $4, L001199C0;
    nop;
L001199DC:
    jal   isceSifSetDChain;
    nop;
    lw    $3, 0x8($29);
    bgez  $3, L00119A3C;
    nop;
    lw    $2, 0x8($29);
    lui   $3, (0x7FFFFFFF >> 16);
    ori   $3, $3, (0x7FFFFFFF & 0xFFFF);
    lw    $4, 0x10($17);
    and   $5, $2, $3;
    slt   $4, $5, $4;
    beqz  $4, L00119A90;
    addiu $2, $0, 0xC;
    lw    $3, 0xC($17);
    mult  $5, $5, $2;
    addu  $2, $5, $3;
    lw    $6, 0x0($2);
    beqz  $6, L00119A90;
    nop;
    lw    $3, 0x8($2);
    daddu $16, $28, $0;
    daddu $28, $3, $0;
    b     L00119A78;
    lw    $2, 0xC($17);
L00119A3C:
    lw    $5, 0x8($29);
    lw    $2, 0x18($17);
    slt   $2, $5, $2;
    beqz  $2, L00119A90;
    addiu $2, $0, 0xC;
    lw    $3, 0x14($17);
    mult  $5, $5, $2;
    addu  $2, $5, $3;
    lw    $6, 0x0($2);
    beqz  $6, L00119A90;
    nop;
    lw    $3, 0x8($2);
    daddu $16, $28, $0;
    daddu $28, $3, $0;
    lw    $2, 0x14($17);
L00119A78:
    daddu $4, $29, $0;
    addu  $2, $5, $2;
    jalr  $31, $6;
    lw    $5, 0x4($2);
    daddu $2, $28, $0;
    daddu $28, $16, $0;
L00119A90:
    sync;
    ei;
    daddu $2, $0, $0;
L00119A9C:
    ld    $31, 0x90($29);
    ld    $17, 0x80($29);
    ld    $16, 0x70($29);
    jr    $31;
    addiu $29, $29, 0xA0;
}
