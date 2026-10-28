#include "types.h"

extern void dpadd(void);
extern void DoubleCmp_13b948(void);

asm void FloorDouble_1283f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    daddu      $6, $4, $0;
    sd         $16, 0x0($29);
    sd         $17, 0x8($29);
    sd         $18, 0x10($29);
    sd         $19, 0x18($29);
    sd         $20, 0x20($29);
    daddu      $2, $6, $0;
    dsll32     $18, $2, 0;
    dsra32     $18, $18, 0;
    dsra32     $16, $2, 0;
    sra        $3, $16, 20;
    andi       $3, $3, 0x7FF;
    addiu      $17, $3, -0x3FF;
    slti       $2, $17, 0x14;
    beqz       $2, L00128508;
    sd        $31, 0x28($29);
    bgez       $17, L001284A0;
    lui       $5, (0xFFFFF >> 16);
    lui        $2, 0x45;
    ld         $5, 0x7940($2);
    jal        dpadd;
    nop;
    daddu      $5, $0, $0;
    daddu      $4, $2, $0;
    jal        DoubleCmp_13b948;
    nop;
    blez       $2, L001285BC;
    nop;
    bltz       $16, L00128480;
    lui       $2, (0x7FFFFFFF >> 16);
    daddu      $18, $0, $0;
    b          L001285BC;
    daddu     $16, $0, $0;
  L00128480:
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    and        $2, $16, $2;
    or         $2, $2, $18;
    beqz       $2, L001285BC;
    nop;
    lui        $16, (0xBFF00000 >> 16);
    b          L001285BC;
    daddu     $18, $0, $0;
  L001284A0:
    daddu      $2, $6, $0;
    ori        $5, $5, (0xFFFFF & 0xFFFF);
    srav       $19, $5, $17;
    and        $3, $16, $19;
    or         $3, $3, $18;
    beql       $3, $0, L001285F0;
    ld        $16, 0x0($29);
    lui        $2, 0x45;
    ld         $5, 0x7940($2);
    jal        dpadd;
    nop;
    daddu      $5, $0, $0;
    daddu      $4, $2, $0;
    jal        DoubleCmp_13b948;
    nop;
    blez       $2, L001285BC;
    nop;
    bgez       $16, L001284FC;
    nor       $2, $0, $19;
    lui        $2, (0x100000 >> 16);
    srav       $2, $2, $17;
    addu       $16, $16, $2;
    nor        $2, $0, $19;
  L001284FC:
    daddu      $18, $0, $0;
    b          L001285BC;
    and       $16, $16, $2;
  L00128508:
    slti       $2, $17, 0x34;
    bnez       $2, L00128538;
    addiu     $2, $3, -0x413;
    addiu      $2, $0, 0x400;
    bne        $17, $2, L001285E8;
    nop;
    daddu      $5, $6, $0;
    jal        dpadd;
    nop;
    b          L001285F0;
    ld        $16, 0x0($29);
    nop;
  L00128538:
    addiu      $3, $0, -0x1;
    srlv       $19, $3, $2;
    daddu      $2, $6, $0;
    and        $3, $18, $19;
    beql       $3, $0, L001285F0;
    ld        $16, 0x0($29);
    lui        $2, 0x45;
    ld         $5, 0x7940($2);
    jal        dpadd;
    nop;
    daddu      $5, $0, $0;
    daddu      $4, $2, $0;
    jal        DoubleCmp_13b948;
    nop;
    blez       $2, L001285BC;
    nop;
    bgez       $16, L001285B8;
    nor       $2, $0, $19;
    addiu      $2, $0, 0x14;
    bne        $17, $2, L00128598;
    addiu     $2, $0, 0x34;
    b          L001285B4;
    addiu     $16, $16, 0x1;
    nop;
  L00128598:
    addiu      $3, $0, 0x1;
    subu       $2, $2, $17;
    sllv       $3, $3, $2;
    addu       $3, $18, $3;
    sltu       $2, $3, $18;
    daddu      $18, $3, $0;
    addu       $16, $16, $2;
  L001285B4:
    nor        $2, $0, $19;
  L001285B8:
    and        $18, $18, $2;
  L001285BC:
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    dsll32     $4, $16, 0;
    and        $20, $20, $3;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    dsll32     $2, $18, 0;
    or         $20, $20, $4;
    dsrl32     $2, $2, 0;
    and        $20, $20, $3;
    or         $6, $20, $2;
  L001285E8:
    daddu      $2, $6, $0;
    ld         $16, 0x0($29);
  L001285F0:
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
