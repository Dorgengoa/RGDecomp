#include "types.h"

extern void sceVu0UnitMatrix(void);
extern void sceVu0MulMatrix(void);

asm void sceVu0ViewScreenMatrix(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    neg.s      $f0, $f17;
    swc1       $f20, 0x60($29);
    neg.s      $f20, $f18;
    lwc1       $f1, 0xA0($29);
    swc1       $f21, 0x68($29);
    add.s      $f0, $f0, $f18;
    mul.s      $f21, $f1, $f19;
    sd         $16, 0x40($29);
    mul.s      $f20, $f20, $f19;
    daddu      $16, $4, $0;
    mul.s      $f17, $f17, $f1;
    swc1       $f26, 0x90($29);
    neg.s      $f19, $f19;
    swc1       $f25, 0x88($29);
    mul.s      $f21, $f21, $f0;
    swc1       $f24, 0x80($29);
    add.s      $f20, $f20, $f17;
    swc1       $f23, 0x78($29);
    add.s      $f19, $f19, $f1;
    swc1       $f22, 0x70($29);
    mov.s      $f22, $f12;
    mov.s      $f24, $f13;
    mov.s      $f23, $f14;
    mov.s      $f26, $f15;
    nop;
    nop;
    div.s      $f21, $f21, $f19;
    nop;
    nop;
    div.s      $f20, $f20, $f19;
    sd         $31, 0x50($29);
    jal        sceVu0UnitMatrix;
    mov.s     $f25, $f16;
    lui        $1, (0x3F800000 >> 16);
    mtc1       $1, $f0;
    daddu      $4, $29, $0;
    swc1       $f22, 0x14($16);
    swc1       $f22, 0x0($16);
    sw         $0, 0x28($16);
    sw         $0, 0x3C($16);
    swc1       $f0, 0x2C($16);
    jal        sceVu0UnitMatrix;
    swc1      $f0, 0x38($16);
    daddu      $4, $16, $0;
    swc1       $f24, 0x0($29);
    swc1       $f23, 0x14($29);
    daddu      $5, $29, $0;
    swc1       $f21, 0x28($29);
    daddu      $6, $4, $0;
    swc1       $f26, 0x30($29);
    swc1       $f25, 0x34($29);
    jal        sceVu0MulMatrix;
    swc1      $f20, 0x38($29);
    ld         $31, 0x50($29);
    ld         $16, 0x40($29);
    lwc1       $f26, 0x90($29);
    lwc1       $f25, 0x88($29);
    lwc1       $f24, 0x80($29);
    lwc1       $f23, 0x78($29);
    lwc1       $f22, 0x70($29);
    lwc1       $f21, 0x68($29);
    lwc1       $f20, 0x60($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}

