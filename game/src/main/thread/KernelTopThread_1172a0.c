#include "types.h"

extern void WaitSema(void);
extern void WakeupThread(void);
extern void RotateThreadReadyQueue(void);
extern void SuspendThread(void);
extern void KprintfSerialMaybe_119308(void);

asm void KernelTopThread_1172a0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $22, 0x60($29);
    sd         $21, 0x50($29);
    lui        $22, 0x48;
    sd         $20, 0x40($29);
    lui        $21, 0x45;
    sd         $19, 0x30($29);
    addiu      $20, $0, 0x1;
    sd         $18, 0x20($29);
    addiu      $19, $0, 0x2;
    sd         $16, 0x0($29);
    addiu      $18, $17, 0x8;
    sd         $31, 0x70($29);
    addiu      $16, $17, 0x9;
  L001172E0:
    jal        WaitSema;
    lw        $4, 0x5FC0($22);
    lw         $3, 0x0($17);
    andi       $3, $3, 0x1FF;
    addiu      $4, $3, 0x1;
    sll        $3, $3, 1;
    sw         $4, 0x0($17);
    addu       $2, $18, $3;
    addu       $6, $16, $3;
    lbu        $2, 0x0($2);
    beq        $2, $20, L00117348;
    slti      $5, $2, 0x2;
    beqz       $5, L00117328;
    addiu     $4, $21, 0x6670;
    beqz       $2, L00117338;
    daddu     $3, $6, $0;
    b          L00117368;
    nop;
  L00117328:
    beq        $2, $19, L00117358;
    addu      $3, $16, $3;
    b          L00117368;
    nop;
  L00117338:
    jal        WakeupThread;
    lbu       $4, 0x0($3);
    b          L001172E0;
    nop;
  L00117348:
    jal        RotateThreadReadyQueue;
    lbu       $4, 0x0($6);
    b          L001172E0;
    nop;
  L00117358:
    jal        SuspendThread;
    lbu       $4, 0x0($3);
    b          L001172E0;
    nop;
  L00117368:
    jal        KprintfSerialMaybe_119308;
    nop;
    b          L001172E0;
    nop;
}
