#include "types.h"

extern void scePrintf_119288(void);
extern void sceDmaPause_10a350(void);

asm void DmaWaitChannelIdle_109bb8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    lui        $17, 0x100;
    sd         $31, 0x30($29);
    daddu      $16, $4, $0;
    sd         $18, 0x20($29);
    lw         $2, 0x0($16);
    andi       $2, $2, 0x100;
    beqz       $2, L00109C10;
    lui       $18, 0x45;
    addiu      $17, $17, -0x1;
  L00109BE8:
    bgez       $17, L00109C00;
    nop;
    jal        scePrintf_119288;
    addiu     $4, $18, 0x6010;
    jal        sceDmaPause_10a350;
    daddu     $4, $16, $0;
  L00109C00:
    lw         $2, 0x0($16);
    andi       $2, $2, 0x100;
    bnez       $2, L00109BE8;
    addiu     $17, $17, -0x1;
  L00109C10:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

