#include "types.h"

extern void KernelSin_126880(void);
extern void dpsub(void);
extern void IeeeRemPio2_123b78(void);
extern void KernelCos_125a58(void);

asm void Sin_128880(void)
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
    bnez       $2, L001288C8;
    sd        $31, 0x10($29);
    daddu      $5, $0, $0;
    jal        KernelSin_126880;
    daddu     $6, $0, $0;
    b          L001289AC;
    ld        $31, 0x10($29);
    nop;
  L001288C8:
    lui        $2, (0x7FEFFFFF >> 16);
    ori        $2, $2, (0x7FEFFFFF & 0xFFFF);
    slt        $2, $2, $6;
    beqz       $2, L001288F0;
    nop;
    jal        dpsub;
    nop;
    b          L001289AC;
    ld        $31, 0x10($29);
    nop;
  L001288F0:
    jal        IeeeRemPio2_123b78;
    daddu     $5, $29, $0;
    addiu      $3, $0, 0x1;
    andi       $4, $2, 0x3;
    beq        $4, $3, L00128948;
    slti      $2, $4, 0x2;
    beql       $2, $0, L00128920;
    addiu     $2, $0, 0x2;
    beqz       $4, L00128930;
    nop;
    b          L00128988;
    nop;
  L00128920:
    beq        $4, $2, L00128960;
    nop;
    b          L00128988;
    nop;
  L00128930:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelSin_126880;
    addiu     $6, $0, 0x1;
    b          L001289AC;
    ld        $31, 0x10($29);
  L00128948:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelCos_125a58;
    nop;
    b          L001289AC;
    ld        $31, 0x10($29);
  L00128960:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelSin_126880;
    addiu     $6, $0, 0x1;
    daddu      $4, $0, $0;
    daddu      $5, $2, $0;
    jal        dpsub;
    nop;
    b          L001289AC;
    ld        $31, 0x10($29);
  L00128988:
    ld         $4, 0x0($29);
    ld         $5, 0x8($29);
    jal        KernelCos_125a58;
    nop;
    daddu      $4, $0, $0;
    daddu      $5, $2, $0;
    jal        dpsub;
    nop;
    ld         $31, 0x10($29);
  L001289AC:
    jr         $31;
    addiu     $29, $29, 0x20;
}
