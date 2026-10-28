#include "types.h"

extern void _iWakeupThread(s32 thread_id);
extern s32 iSignalSema(s32 sema_id);

/* Naked `asm void` (lever 6). D_004461F8/D_00485FC8/D_00485FC0 hi/lo
   hardcoded per lever 5 (all positive 16-bit los, no sign adjustment
   needed here). */

asm void iWakeupThread_117468(void)
{
    .set noreorder;
    addiu $29, $29, -0x20;
    sd    $31, 0x10($29);
    sd    $16, 0x0($29);
    addiu $3, $0, -0x2F;
    syscall 0;
    daddu $16, $2, $0;
    beq   $16, $4, L00117498;
    sltiu $2, $16, 0x100;
    jal   _iWakeupThread;
    nop;
    b     L001174F0;
    ld    $31, 0x10($29);
L00117498:
    beqz  $2, L001174AC;
    lui   $2, 0x44;
    lw    $3, 0x61F8($2);
    bnez  $3, L001174B4;
    lui   $3, 0x48;
L001174AC:
    b     L001174EC;
    addiu $2, $0, -0x1;
L001174B4:
    lui   $5, 0x48;
    addiu $3, $3, 0x5FC8;
    lw    $4, 0x5FC0($5);
    lw    $2, 0x4($3);
    andi  $2, $2, 0x1FF;
    sll   $6, $2, 1;
    addiu $2, $2, 0x1;
    addu  $5, $3, $6;
    sw    $2, 0x4($3);
    daddu $3, $5, $0;
    sb    $0, 0x8($5);
    jal   iSignalSema;
    sb    $16, 0x9($3);
    daddu $2, $16, $0;
L001174EC:
    ld    $31, 0x10($29);
L001174F0:
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x20;
}
