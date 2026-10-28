#include "types.h"

extern void DoubleCmp_13b948(void);
extern void dpsub(void);
extern void DoubleToU64_13ab28(void);

asm void DoubleToS64_13ac40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $17, 0x8($29);
    daddu      $17, $0, $0;
    daddu      $5, $17, $0;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    daddu      $16, $4, $0;
    jal        DoubleCmp_13b948;
    nop;
    daddu      $4, $16, $0;
    daddu      $5, $16, $0;
    bgezl      $2, L0013ACA8;
    ld        $16, 0x0($29);
    daddu      $4, $17, $0;
    jal        dpsub;
    nop;
    daddu      $4, $2, $0;
    jal        DoubleToU64_13ab28;
    nop;
    ld         $16, 0x0($29);
    dsubu      $2, $0, $2;
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
    nop;
  L0013ACA8:
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    j          DoubleToU64_13ab28;
    addiu     $29, $29, 0x20;
}

