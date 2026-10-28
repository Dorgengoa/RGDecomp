#include "types.h"

extern void Cosf_128d30(void);
extern void Sinf_128fd0(void);

asm void MtxRotY_13ce20(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sq         $16, 0x10($29);
    swc1       $f20, 0x0($29);
    daddu      $16, $4, $0;
    mov.s      $f20, $f12;
    vmr32.xyzw $vf1, $vf0;
    vmr32.xyzw $vf2, $vf1;
    vmr32.xyzw $vf3, $vf2;
    sqc2       $vf0, 0x30($16);
    sqc2       $vf1, 0x20($16);
    sqc2       $vf2, 0x10($16);
    jal        Cosf_128d30;
    sqc2      $vf3, 0x0($16);
    swc1       $f0, 0x28($16);
    mov.s      $f12, $f20;
    jal        Sinf_128fd0;
    swc1      $f0, 0x0($16);
    swc1       $f0, 0x20($16);
    neg.s      $f0, $f0;
    swc1       $f0, 0x8($16);
    ld         $31, 0x20($29);
    lwc1       $f20, 0x0($29);
    lq         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

