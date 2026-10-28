#include "types.h"

extern void KernelCos_125a58(void);
extern void dpsub(void);
extern void IeeeRemPio2_123b78(void);
extern void KernelSin_126880(void);

asm void Cos_128278(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $5, $4, $0;
    daddu      $2, $5, $0;
    dsra32     $6, $2, 0;
    lui        $3, (0x7FFFFFFF >> 16);
    lui        $2, (0x3FE921FB >> 16);
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    ori        $2, $2, (0x3FE921FB & 0xFFFF);
    and        $6, $6, $3;
    slt        $2, $2, $6;
    bnez       $2, L001282C0;
    sd        $31, 0x10($29);
    daddu      $5, $0, $0;
    jal        KernelCos_125a58;
    nop;
    b          L00128394;
    ld        $31, 0x10($29);
    nop;
  L001282C0:
    lui        $2, (0x7FEFFFFF >> 16);
    ori        $2, $2, (0x7FEFFFFF & 0xFFFF);
    slt        $2, $2, $6;
    beqz       $2, L001282E8;
    nop;
    jal        dpsub;
    nop;
    b          L00128394;
    ld        $31, 0x10($29);
    nop;
  L001282E8:
    jal        IeeeRemPio2_123b78;
    daddu     $5, $29, $0;
    addiu      $3, $0, 0x1;
    andi       $4, $2, 0x3;
    beq        $4, $3, L00128340;
    slti      $2, $4, 0x2;
    beql       $2, $0, L00128318;
    addiu     $2, $0, 0x2;
    beqz       $4, L00128328;
    nop;
    b          L00128380;
    nop;
  L00128318:
    beq        $4, $2, L00128358;
    nop;
    b          L00128380;
    nop;
  L00128328:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelCos_125a58;
    nop;
    b          L00128394;
    ld        $31, 0x10($29);
  L00128340:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelSin_126880;
    addiu     $6, $0, 0x1;
    b          L00128368;
    nop;
  L00128358:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelCos_125a58;
    nop;
  L00128368:
    daddu      $4, $0, $0;
    daddu      $5, $2, $0;
    jal        dpsub;
    nop;
    b          L00128394;
    ld        $31, 0x10($29);
  L00128380:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelSin_126880;
    addiu     $6, $0, 0x1;
    ld         $31, 0x10($29);
  L00128394:
    jr         $31;
    addiu     $29, $29, 0x20;
}
