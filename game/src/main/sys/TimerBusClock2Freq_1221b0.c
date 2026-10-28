#include "types.h"

extern void S64ToFloat_13aa40(void);

asm void TimerBusClock2Freq_1221b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    bltz       $4, L001221CC;
    sd        $31, 0x0($29);
    jal        S64ToFloat_13aa40;
    nop;
    b          L001221E0;
    mov.s     $f1, $f0;
  L001221CC:
    dsrl       $2, $4, 1;
    andi       $4, $4, 0x1;
    jal        S64ToFloat_13aa40;
    or        $4, $4, $2;
    add.s      $f1, $f0, $f0;
  L001221E0:
    lui        $1, (0x4D0CA000 >> 16);
    ori        $1, $1, (0x4D0CA000 & 0xFFFF);
    mtc1       $1, $f0;
    ld         $31, 0x0($29);
    nop;
    nop;
    div.s      $f0, $f0, $f1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
