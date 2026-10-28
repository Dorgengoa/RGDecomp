#include "types.h"

extern void S64ToDouble_13a998(void);
extern void dpadd(void);

asm void U64ToDouble_100370(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    blez       $4, L0010038C;
    sd        $31, 0x0($29);
    jal        S64ToDouble_13a998;
    nop;
    b          L001003AC;
    ld        $31, 0x0($29);
  L0010038C:
    dsrl       $3, $4, 1;
    andi       $2, $4, 0x1;
    jal        S64ToDouble_13a998;
    or        $4, $3, $2;
    daddu      $4, $2, $0;
    jal        dpadd;
    daddu     $5, $2, $0;
    ld         $31, 0x0($29);
  L001003AC:
    jr         $31;
    addiu     $29, $29, 0x10;
}

