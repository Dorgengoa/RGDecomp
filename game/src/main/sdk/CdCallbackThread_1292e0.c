#include "types.h"

extern void WaitSema(void);
extern void ExitDeleteThread(void);
extern void scePrintf_119288(void);

asm void CdCallbackThread_1292e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    sd         $30, 0x80($29);
    sd         $23, 0x70($29);
    lui        $30, 0x49;
    sd         $22, 0x60($29);
    lui        $23, 0x44;
    sd         $21, 0x50($29);
    lui        $22, 0x45;
    sd         $20, 0x40($29);
    lui        $21, 0x49;
    sd         $19, 0x30($29);
    lui        $20, 0x44;
    sd         $18, 0x20($29);
    lui        $19, 0x44;
    sd         $17, 0x10($29);
    lui        $18, 0x49;
    sd         $31, 0x90($29);
    lui        $17, 0x44;
    sd         $16, 0x0($29);
    lui        $2, 0x44;
  L00129330:
    jal        WaitSema;
    lw        $4, 0x7960($2);
    lw         $3, 0x79A0($20);
    addiu      $2, $0, -0x1;
    bne        $3, $2, L00129364;
    lw        $2, 0x7950($23);
    sw         $0, 0x7974($19);
    lui        $2, 0x44;
    sw         $0, 0x79A0($20);
    sw         $0, 0x7954($2);
    jal        ExitDeleteThread;
    sw        $0, -0x15AC($30);
    lw         $2, 0x7950($23);
  L00129364:
    blez       $2, L00129378;
    addiu     $4, $22, 0x79D8;
    lw         $5, -0x15C0($18);
    jal        scePrintf_119288;
    lw        $6, 0x79A4($17);
  L00129378:
    lw         $3, -0x15C0($18);
    beqz       $3, L001293A4;
    nop;
    lw         $2, 0x79A4($17);
    beqz       $2, L001293A4;
    nop;
    daddu      $16, $28, $0;
    lw         $28, -0x15BC($21);
    jalr $31, $3;
    lw        $4, 0x79A4($17);
    daddu      $28, $16, $0;
  L001293A4:
    sw         $0, 0x7974($19);
    b          L00129330;
    lui       $2, 0x44;
}

