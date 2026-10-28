#include "types.h"

extern void SetVTLBRefillHandler(void);
extern void SetVCommonHandler_116260(void);

asm void SetDebugHandler_11fe40(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    addiu      $29, $29, -0x20;
    addiu      $4, $6, -0x1;
    sd         $31, 0x10($29);
    sltiu      $2, $4, 0xD;
    bnez       $2, L0011FE68;
    sd        $16, 0x0($29);
    lui        $2, (0xFFFFFFFF >> 16);
    b          L0011FEB4;
    ori       $2, $2, (0xFFFFFFFF & 0xFFFF);
  L0011FE68:
    lui        $2, 0x44;
    sll        $3, $6, 2;
    addiu      $2, $2, 0x6600;
    sltiu      $4, $4, 0x3;
    addu       $3, $3, $2;
    lw         $16, 0x0($3);
    beqz       $4, L0011FEA0;
    sw        $5, 0x0($3);
    lui        $5, 0x12;
    daddu      $4, $6, $0;
    jal        SetVTLBRefillHandler;
    addiu     $5, $5, 0x540;
    b          L0011FEB4;
    daddu     $2, $16, $0;
  L0011FEA0:
    lui        $5, 0x12;
    daddu      $4, $6, $0;
    jal        SetVCommonHandler_116260;
    addiu     $5, $5, 0x540;
    daddu      $2, $16, $0;
  L0011FEB4:
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
