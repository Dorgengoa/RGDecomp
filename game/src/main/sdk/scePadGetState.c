#include "types.h"

extern void scePadGetDmaStr(void);

asm void scePadGetState(void)
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
    bnez       $3, L0012B8B8;
    daddu     $4, $6, $0;
    b          L0012B8E4;
    addiu     $2, $0, 0x63;
  L0012B8B8:
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lbu        $3, 0x70($29);
    addiu      $2, $0, 0x6;
    bne        $3, $2, L0012B8E4;
    lbu       $2, 0x70($29);
    lbu        $3, 0x71($29);
    addiu      $2, $0, 0x2;
    bne        $3, $2, L0012B8E4;
    lbu       $2, 0x70($29);
    addiu      $2, $0, 0x5;
  L0012B8E4:
    ld         $31, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
