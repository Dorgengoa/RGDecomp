#include "types.h"

extern void dpmul(void);

asm void MprecLog10_132c98(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    slti       $2, $16, 0x18;
    ori        $4, $0, 0xFFC0;
    dsll32     $4, $4, 14;
    beqz       $2, L00132CD0;
    sd        $31, 0x8($29);
    sll        $3, $16, 3;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    ld         $2, -0x7FA8($2);
    b          L00132CFC;
    ld        $16, 0x0($29);
  L00132CD0:
    blez       $16, L00132CF4;
    nop;
  L00132CD8:
    ori        $5, $0, 0x8048;
    dsll32     $5, $5, 15;
    jal        dpmul;
    addiu     $16, $16, -0x1;
    daddu      $4, $2, $0;
    bgtz       $16, L00132CD8;
    nop;
  L00132CF4:
    daddu      $2, $4, $0;
    ld         $16, 0x0($29);
  L00132CFC:
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
