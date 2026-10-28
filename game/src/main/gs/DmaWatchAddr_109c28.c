#include "types.h"

extern void scePrintf_119288(void);
extern void sceDmaPause_10a350(void);

asm void DmaWatchAddr_109c28(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $31, 0x40($29);
    lui        $16, (0x1000000 >> 16);
    sd         $19, 0x30($29);
    movn       $16, $6, $6;
    lw         $2, 0x10($17);
    sltu       $2, $2, $18;
    beqz       $2, L00109C90;
    lui       $19, 0x45;
    addiu      $16, $16, -0x1;
    nop;
  L00109C68:
    bgez       $16, L00109C80;
    nop;
    jal        scePrintf_119288;
    addiu     $4, $19, 0x6010;
    jal        sceDmaPause_10a350;
    daddu     $4, $17, $0;
  L00109C80:
    lw         $2, 0x10($17);
    sltu       $2, $2, $18;
    bnez       $2, L00109C68;
    addiu     $16, $16, -0x1;
  L00109C90:
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

