#include "types.h"

extern void litodp(void);
extern void dpmul(void);
extern void dpadd(void);
extern void dptofp(void);

asm void S64ToFloat_13aa40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 11;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    daddu      $2, $17, $2;
    addiu      $3, $0, -0x1;
    dsll       $3, $3, 11;
    dsrl       $3, $3, 10;
    sltu       $3, $3, $2;
    andi       $2, $17, 0x7FF;
    sd         $16, 0x0($29);
    sd         $18, 0x10($29);
    beqz       $3, L0013AA88;
    sd        $31, 0x18($29);
    beqz       $2, L0013AA88;
    addiu     $2, $0, 0x800;
    or         $17, $17, $2;
  L0013AA88:
    ori        $16, $0, 0x81E0;
    dsll32     $16, $16, 15;
    dsra32     $4, $17, 0;
    jal        litodp;
    nop;
    daddu      $4, $2, $0;
    daddu      $5, $16, $0;
    jal        dpmul;
    nop;
    daddu      $5, $16, $0;
    lui        $16, (0xFFFF0000 >> 16);
    dsrl32     $16, $16, 0;
    daddu      $4, $2, $0;
    jal        dpmul;
    and       $16, $17, $16;
    dsll32     $16, $16, 0;
    dsra32     $16, $16, 0;
    daddu      $18, $2, $0;
    jal        litodp;
    daddu     $4, $16, $0;
    ori        $5, $0, 0x83E0;
    dsll32     $5, $5, 15;
    bgez       $16, L0013AAF4;
    nop;
    daddu      $4, $2, $0;
    jal        dpadd;
    nop;
  L0013AAF4:
    daddu      $5, $2, $0;
    daddu      $4, $18, $0;
    jal        dpadd;
    nop;
    daddu      $4, $2, $0;
    jal        dptofp;
    nop;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

