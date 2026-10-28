#include "types.h"

extern void KernelTanf_127ae0(void);
extern void RemPio2f_1255d8(void);

asm void Tanf_1290b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    mov.s      $f0, $f12;
    sd         $31, 0x20($29);
    swc1       $f0, 0x10($29);
    lui        $3, (0x7FFFFFFF >> 16);
    mtc1       $0, $f13;
    lw         $5, 0x10($29);
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    lui        $2, (0x3F490FDA >> 16);
    and        $3, $5, $3;
    ori        $2, $2, (0x3F490FDA & 0xFFFF);
    slt        $2, $2, $3;
    bnez       $2, L00129100;
    daddu     $4, $29, $0;
    jal        KernelTanf_127ae0;
    addiu     $4, $0, 0x1;
    b          L00129128;
    ld        $31, 0x20($29);
  L00129100:
    jal        RemPio2f_1255d8;
    nop;
    addiu      $4, $0, 0x1;
    andi       $2, $2, 0x1;
    lwc1       $f12, 0x0($29);
    sll        $2, $2, 1;
    lwc1       $f13, 0x4($29);
    jal        KernelTanf_127ae0;
    subu      $4, $4, $2;
    ld         $31, 0x20($29);
  L00129128:
    jr         $31;
    addiu     $29, $29, 0x30;
}
