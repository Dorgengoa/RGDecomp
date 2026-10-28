#include "types.h"

extern void Timer2SetMode_120f50(s32);
extern s32 TimerAlarmUnlink_1214d8(void *);
extern void TimerAlarmInsertSorted_121450(void *);
extern void SetNextComp_1212c0(void *, s32);

/* Naked `asm void` (lever 6), the biggest unit in the lane. D_004478A8's
   hi/lo hardcoded per lever 5: hi=0x44 (once, `lui $21`), lo=0x78A8
   (constant EVERY place it appears, whichever register holds the base --
   confirmed by decoding all nine occurrences). Every other `lui`/`ori`
   pair in this unit is already a plain numeric MMIO constant in the
   original listing, copied verbatim. */

asm void TimerAlarmIntcHandler_121510(void)
{
    .set noreorder;
    addiu $29, $29, -0x90;
    lui   $3, (0x10001010 >> 16);
    sd    $22, 0x60($29);
    ori   $3, $3, (0x10001010 & 0xFFFF);
    sd    $31, 0x80($29);
    daddu $22, $6, $0;
    sd    $23, 0x70($29);
    sd    $21, 0x50($29);
    sd    $20, 0x40($29);
    sd    $19, 0x30($29);
    sd    $18, 0x20($29);
    sd    $17, 0x10($29);
    sd    $16, 0x0($29);
    lw    $2, 0x0($3);
    andi  $2, $2, 0x400;
    beqz  $2, L001216C0;
    lui   $21, 0x44;
    addiu $2, $21, 0x78A8;
    lw    $16, 0x18($2);
    beqz  $16, L001216C0;
    daddu $20, $21, $0;
    addiu $23, $0, 0x3999;
    lui   $2, (0x10001000 >> 16);
    nop;
L00121570:
    lui   $3, (0x10001010 >> 16);
    ori   $2, $2, (0x10001000 & 0xFFFF);
    ori   $3, $3, (0x10001010 & 0xFFFF);
    lw    $6, 0x0($2);
    lw    $17, 0x0($3);
    ld    $4, 0x20($16);
    ld    $2, 0x10($16);
    andi  $5, $17, 0x800;
    ld    $3, 0x18($16);
    daddu $4, $4, $2;
    beqz  $5, L001215C4;
    dsubu $19, $4, $3;
    ld    $2, 0x78A8($20);
    lui   $4, (0xFFFFFBFF >> 16);
    ori   $4, $4, (0xFFFFFBFF & 0xFFFF);
    daddiu $2, $2, 0x1;
    and   $4, $17, $4;
    jal   Timer2SetMode_120f50;
    sd    $2, 0x78A8($20);
    lui   $6, (0x10001000 >> 16);
    lw    $6, (0x10001000 & 0xFFFF)($6);
L001215C4:
    ld    $4, 0x78A8($20);
    dsll32 $2, $6, 0;
    dsrl32 $2, $2, 0;
    andi  $3, $17, 0x3;
    dsll  $4, $4, 16;
    sll   $3, $3, 2;
    or    $4, $4, $2;
    dsllv $17, $4, $3;
    sltu  $2, $17, $19;
    bnez  $2, L001216C0;
    addiu $18, $20, 0x78A8;
    jal   TimerAlarmUnlink_1214d8;
    daddu $4, $16, $0;
    daddu $19, $2, $0;
    ld    $6, 0x18($16);
    lw    $2, 0x8($16);
    sll   $7, $16, 4;
    ld    $3, 0x10($16);
    daddu $6, $17, $6;
    or    $2, $7, $2;
    sw    $2, 0x1C($18);
    dsubu $6, $6, $3;
    lw    $28, 0x2C($16);
    lw    $4, 0x8($16);
    daddu $8, $22, $0;
    lw    $2, 0x28($16);
    or    $4, $7, $4;
    ld    $5, 0x20($16);
    jalr  $31, $2;
    lw    $7, 0x30($16);
    daddu $5, $2, $0;
    bnez  $5, L00121660;
    addiu $2, $0, -0x1;
    lw    $3, 0xC($16);
    lui   $2, (0xFFFFFFFD >> 16);
    ori   $2, $2, (0xFFFFFFFD & 0xFFFF);
    and   $3, $3, $2;
    b     L001216AC;
    sw    $3, 0xC($16);
L00121660:
    bne   $5, $2, L00121690;
    addiu $2, $0, 0x3998;
    sw    $0, 0x8($16);
    sw    $0, 0xC($16);
    lw    $3, 0x14($18);
    lw    $2, 0x10($18);
    sw    $3, 0x0($16);
    addiu $2, $2, -0x1;
    sw    $16, 0x14($18);
    sw    $2, 0x10($18);
    b     L001216B0;
    daddu $16, $19, $0;
L00121690:
    ld    $3, 0x20($16);
    sltu  $2, $2, $5;
    daddu $4, $16, $0;
    movz  $5, $23, $2;
    daddu $3, $3, $5;
    jal   TimerAlarmInsertSorted_121450;
    sd    $3, 0x20($16);
L001216AC:
    daddu $16, $19, $0;
L001216B0:
    bnez  $16, L00121570;
    lui   $2, (0x10001000 >> 16);
    b     L001216C4;
    addiu $4, $21, 0x78A8;
L001216C0:
    addiu $4, $21, 0x78A8;
L001216C4:
    addiu $3, $0, -0x1;
    sw    $3, 0x1C($4);
    lui   $2, (0x10001000 >> 16);
    ori   $2, $2, (0x10001000 & 0xFFFF);
    lui   $3, (0x10001010 >> 16);
    lw    $4, 0x0($2);
    ori   $3, $3, (0x10001010 & 0xFFFF);
    lw    $16, 0x0($3);
    andi  $2, $16, 0x800;
    beqz  $2, L00121714;
    nop;
    ld    $2, 0x78A8($21);
    lui   $4, (0xFFFFFBFF >> 16);
    ori   $4, $4, (0xFFFFFBFF & 0xFFFF);
    daddiu $2, $2, 0x1;
    and   $4, $16, $4;
    jal   Timer2SetMode_120f50;
    sd    $2, 0x78A8($21);
    lui   $4, (0x10001000 >> 16);
    lw    $4, (0x10001000 & 0xFFFF)($4);
L00121714:
    ld    $2, 0x78A8($21);
    dsll32 $3, $4, 0;
    dsrl32 $3, $3, 0;
    andi  $4, $16, 0x3;
    dsll  $2, $2, 16;
    sll   $4, $4, 2;
    or    $2, $2, $3;
    jal   SetNextComp_1212c0;
    dsllv $4, $2, $4;
    lui   $2, (0x10001000 >> 16);
    lw    $2, (0x10001000 & 0xFFFF)($2);
    lui   $3, (0x10001010 >> 16);
    lw    $3, (0x10001010 & 0xFFFF)($3);
    andi  $2, $3, 0x800;
    beqz  $2, L00121778;
    nop;
    ld    $2, 0x78A8($21);
    lui   $4, (0xFFFFFBFF >> 16);
    ori   $4, $4, (0xFFFFFBFF & 0xFFFF);
    daddiu $2, $2, 0x1;
    and   $4, $3, $4;
    jal   Timer2SetMode_120f50;
    sd    $2, 0x78A8($21);
    lui   $2, (0x10001000 >> 16);
    lw    $2, (0x10001000 & 0xFFFF)($2);
L00121778:
    ld    $2, 0x78A8($21);
    sync;
    ei;
    ld    $31, 0x80($29);
    daddu $2, $0, $0;
    ld    $23, 0x70($29);
    ld    $22, 0x60($29);
    ld    $21, 0x50($29);
    ld    $20, 0x40($29);
    ld    $19, 0x30($29);
    ld    $18, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x90;
}
