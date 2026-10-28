#include "types.h"

extern void S64ToDouble_13a998(void);
extern void dpadd(void);

asm void UIntToDouble_100320(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    dsll32     $4, $4, 0;
    dsrl32     $4, $4, 0;
    blez       $4, L00100344;
    sd        $31, 0x0($29);
    jal        S64ToDouble_13a998;
    nop;
    b          L00100364;
    ld        $31, 0x0($29);
  L00100344:
    dsrl       $3, $4, 1;
    andi       $2, $4, 0x1;
    jal        S64ToDouble_13a998;
    or        $4, $3, $2;
    daddu      $4, $2, $0;
    jal        dpadd;
    daddu     $5, $2, $0;
    ld         $31, 0x0($29);
  L00100364:
    jr         $31;
    addiu     $29, $29, 0x10;
}

