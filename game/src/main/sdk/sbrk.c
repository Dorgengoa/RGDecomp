#include "types.h"

extern s32 EndOfHeap(void);
extern void GetReent_12f4d0(void);

/* Naked `asm void` (lever 6). D_004461F4 hi/lo hardcoded per lever 5
   (registered name is `sbrk`, stale lane-file name FUN_00116ca0). */

asm void sbrk(void)
{
    .set noreorder;
    addiu $29, $29, -0x40;
    sd    $31, 0x30($29);
    sd    $18, 0x20($29);
    sd    $17, 0x10($29);
    sd    $16, 0x0($29);
    mfc0  $17, $12;
    lui   $2, (0x10000 >> 16);
    and   $17, $17, $2;
    beqz  $17, L00116CEC;
    lui   $18, 0x44;
L00116CC8:
    di;
    sync.p;
    mfc0  $2, $12;
    lui   $3, (0x10000 >> 16);
    and   $2, $2, $3;
    bnez  $2, L00116CC8;
    nop;
    b     L00116CF0;
    lw    $2, 0x61F4($18);
L00116CEC:
    lw    $2, 0x61F4($18);
L00116CF0:
    jal   EndOfHeap;
    addu  $16, $2, $4;
    sltu  $2, $2, $16;
    beqz  $2, L00116D28;
    lw    $2, 0x61F4($18);
    jal   GetReent_12f4d0;
    nop;
    addiu $3, $0, 0xC;
    beqz  $17, L00116D1C;
    sw    $3, 0x0($2);
    ei;
L00116D1C:
    lui   $2, (0xFFFFFFFF >> 16);
    b     L00116D34;
    ori   $2, $2, (0xFFFFFFFF & 0xFFFF);
L00116D28:
    beqz  $17, L00116D34;
    sw    $16, 0x61F4($18);
    ei;
L00116D34:
    ld    $31, 0x30($29);
    ld    $18, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x40;
}
