#include "types.h"

extern void _iSuspendThread(s32 thread_id);
extern s32 iSignalSema(s32 sema_id);

/* Sibling of iWakeupThread_117468 (calls _iSuspendThread, sets an extra flag
   byte to 2 instead of 0). */

asm void iSuspendThread_117580(void)
{
    .set noreorder;
    addiu $29, $29, -0x20;
    sd    $31, 0x10($29);
    sd    $16, 0x0($29);
    addiu $3, $0, -0x2F;
    syscall 0;
    daddu $16, $2, $0;
    beq   $16, $4, L001175B0;
    sltiu $2, $16, 0x100;
    jal   _iSuspendThread;
    nop;
    b     L0011760C;
    ld    $31, 0x10($29);
L001175B0:
    beqz  $2, L001175C4;
    lui   $2, 0x44;
    lw    $3, 0x61F8($2);
    bnez  $3, L001175CC;
    lui   $3, 0x48;
L001175C4:
    b     L00117608;
    addiu $2, $0, -0x1;
L001175CC:
    lui   $5, 0x48;
    addiu $3, $3, 0x5FC8;
    lw    $4, 0x5FC0($5);
    lw    $2, 0x4($3);
    addiu $7, $0, 0x2;
    andi  $2, $2, 0x1FF;
    sll   $6, $2, 1;
    addiu $2, $2, 0x1;
    addu  $5, $3, $6;
    sw    $2, 0x4($3);
    sb    $7, 0x8($5);
    daddu $3, $5, $0;
    jal   iSignalSema;
    sb    $16, 0x9($3);
    daddu $2, $16, $0;
L00117608:
    ld    $31, 0x10($29);
L0011760C:
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x20;
}
