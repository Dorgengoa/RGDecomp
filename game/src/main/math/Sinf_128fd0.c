#include "types.h"

extern void KernelSinf_1279d8(void);
extern void RemPio2f_1255d8(void);
extern void KernelCosf_127020(void);

asm void Sinf_128fd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    mov.s      $f0, $f12;
    sd         $31, 0x20($29);
    swc1       $f0, 0x10($29);
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $3, (0x3F490FD8 >> 16);
    lw         $4, 0x10($29);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    ori        $3, $3, (0x3F490FD8 & 0xFFFF);
    and        $2, $4, $2;
    slt        $3, $3, $2;
    bnez       $3, L00129018;
    nop;
    mtc1       $0, $f13;
    jal        KernelSinf_1279d8;
    daddu     $4, $0, $0;
    b          L001290B0;
    ld        $31, 0x20($29);
  L00129018:
    jal        RemPio2f_1255d8;
    daddu     $4, $29, $0;
    addiu      $3, $0, 0x1;
    andi       $4, $2, 0x3;
    beq        $4, $3, L00129070;
    slti      $2, $4, 0x2;
    beql       $2, $0, L00129048;
    addiu     $2, $0, 0x2;
    beqz       $4, L00129058;
    lwc1      $f12, 0x0($29);
    b          L001290A0;
    nop;
  L00129048:
    beq        $4, $2, L00129088;
    lwc1      $f12, 0x0($29);
    b          L001290A0;
    nop;
  L00129058:
    addiu      $4, $0, 0x1;
    jal        KernelSinf_1279d8;
    lwc1      $f13, 0x4($29);
    b          L001290B0;
    ld        $31, 0x20($29);
    nop;
  L00129070:
    lwc1       $f12, 0x0($29);
    jal        KernelCosf_127020;
    lwc1      $f13, 0x4($29);
    b          L001290B0;
    ld        $31, 0x20($29);
    nop;
  L00129088:
    addiu      $4, $0, 0x1;
    jal        KernelSinf_1279d8;
    lwc1      $f13, 0x4($29);
    b          L001290AC;
    neg.s     $f0, $f0;
    nop;
  L001290A0:
    jal        KernelCosf_127020;
    lwc1      $f13, 0x4($29);
    neg.s      $f0, $f0;
  L001290AC:
    ld         $31, 0x20($29);
  L001290B0:
    jr         $31;
    addiu     $29, $29, 0x30;
}
