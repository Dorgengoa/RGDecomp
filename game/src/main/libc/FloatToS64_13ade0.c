#include "types.h"

extern void FloatToU64_13acb8(void);

asm void FloatToS64_13ade0(void)
{
    .set noreorder;
    mtc1       $0, $f0;
    mov.s      $f1, $f12;
    addiu      $29, $29, -0x10;
    c.lt.s     $f1, $f0;
    bc1f       L0013AE10;
    sd        $31, 0x0($29);
    jal        FloatToU64_13acb8;
    neg.s     $f12, $f1;
    ld         $31, 0x0($29);
    dsubu      $2, $0, $2;
    jr         $31;
    addiu     $29, $29, 0x10;
  L0013AE10:
    ld         $31, 0x0($29);
    j          FloatToU64_13acb8;
    addiu     $29, $29, 0x10;
}

