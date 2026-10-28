#include "types.h"

extern void litodp(void);
extern void dpmul(void);
extern void dpadd(void);

asm void S64ToDouble_13a998(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x8($29);
    dsra32     $4, $16, 0;
    ori        $17, $0, 0x81E0;
    dsll32     $17, $17, 15;
    sd         $31, 0x10($29);
    jal        litodp;
    nop;
    daddu      $4, $2, $0;
    daddu      $5, $17, $0;
    jal        dpmul;
    nop;
    daddu      $5, $17, $0;
    daddu      $4, $2, $0;
    jal        dpmul;
    nop;
    daddu      $17, $2, $0;
    lui        $2, (0xFFFF0000 >> 16);
    dsrl32     $2, $2, 0;
    and        $16, $16, $2;
    dsll32     $16, $16, 0;
    dsra32     $16, $16, 0;
    jal        litodp;
    daddu     $4, $16, $0;
    ori        $5, $0, 0x83E0;
    dsll32     $5, $5, 15;
    bgez       $16, L0013AA1C;
    nop;
    daddu      $4, $2, $0;
    jal        dpadd;
    nop;
  L0013AA1C:
    daddu      $4, $17, $0;
    daddu      $5, $2, $0;
    jal        dpadd;
    nop;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

