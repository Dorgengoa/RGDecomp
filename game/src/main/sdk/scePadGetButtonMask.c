#include "types.h"

extern void scePadGetDmaStr(void);

asm void scePadGetButtonMask(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $6, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0x90;
    lui        $2, 0x49;
    sd         $31, 0x80($29);
    addiu      $2, $2, -0x12B0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    beqz       $3, L0012C080;
    daddu     $4, $6, $0;
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lbu        $3, 0x72($29);
    addiu      $2, $0, 0x1;
    beq        $3, $2, L0012C088;
    lbu       $2, 0x64($29);
  L0012C080:
    b          L0012C0D4;
    daddu     $2, $0, $0;
  L0012C088:
    sltiu      $2, $2, 0x2;
    bnez       $2, L0012C0D4;
    daddu     $2, $0, $0;
    lbu        $2, 0x66($29);
    sltiu      $2, $2, 0x2;
    bnez       $2, L0012C0D4;
    daddu     $2, $0, $0;
    lbu        $5, 0x7C($29);
    lbu        $3, 0x7B($29);
    lbu        $4, 0x7A($29);
    dsll       $5, $5, 24;
    lbu        $2, 0x79($29);
    dsll       $3, $3, 16;
    dsll       $4, $4, 8;
    daddu      $2, $2, $5;
    daddu      $3, $3, $4;
    daddu      $2, $2, $3;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
  L0012C0D4:
    ld         $31, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
