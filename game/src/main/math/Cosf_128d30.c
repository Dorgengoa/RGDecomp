#include "types.h"

extern void KernelCosf_127020(void);
extern void RemPio2f_1255d8(void);
extern void KernelSinf_1279d8(void);

asm void Cosf_128d30(void)
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
    bnez       $3, L00128D78;
    nop;
    mtc1       $0, $f13;
    jal        KernelCosf_127020;
    nop;
    b          L00128DFC;
    ld        $31, 0x20($29);
  L00128D78:
    jal        RemPio2f_1255d8;
    daddu     $4, $29, $0;
    addiu      $3, $0, 0x1;
    andi       $4, $2, 0x3;
    beq        $4, $3, L00128DC8;
    slti      $2, $4, 0x2;
    beql       $2, $0, L00128DA8;
    addiu     $2, $0, 0x2;
    beqz       $4, L00128DB8;
    lwc1      $f12, 0x0($29);
    b          L00128DF0;
    addiu     $4, $0, 0x1;
  L00128DA8:
    beq        $4, $2, L00128DE0;
    lwc1      $f12, 0x0($29);
    b          L00128DF0;
    addiu     $4, $0, 0x1;
  L00128DB8:
    jal        KernelCosf_127020;
    lwc1      $f13, 0x4($29);
    b          L00128DFC;
    ld        $31, 0x20($29);
  L00128DC8:
    lwc1       $f12, 0x0($29);
    addiu      $4, $0, 0x1;
    jal        KernelSinf_1279d8;
    lwc1      $f13, 0x4($29);
    b          L00128DF8;
    neg.s     $f0, $f0;
  L00128DE0:
    jal        KernelCosf_127020;
    lwc1      $f13, 0x4($29);
    b          L00128DF8;
    neg.s     $f0, $f0;
  L00128DF0:
    jal        KernelSinf_1279d8;
    lwc1      $f13, 0x4($29);
  L00128DF8:
    ld         $31, 0x20($29);
  L00128DFC:
    jr         $31;
    addiu     $29, $29, 0x30;
}
