#include "types.h"

extern void deci2Putchar(void);

asm void PrintfDeci2PutcCb_1190f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $4, $6, $0;
    beqz       $4, L00119110;
    sd        $31, 0x0($29);
    jal        deci2Putchar;
    nop;
  L00119110:
    ld         $31, 0x0($29);
    addiu      $2, $0, 0x1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
