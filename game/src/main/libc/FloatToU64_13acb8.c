#include "types.h"

extern void fptodp(void);
extern void DoubleCmp_13b948(void);
extern void dpmul(void);
extern void DoubleToUInt_13bb78(void);
extern void S64ToDouble_13a998(void);
extern void dpadd(void);
extern void dpsub(void);

asm void FloatToU64_13acb8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $17, 0x8($29);
    sd         $16, 0x0($29);
    sd         $18, 0x10($29);
    sd         $31, 0x18($29);
    jal        fptodp;
    nop;
    daddu      $17, $2, $0;
    daddu      $5, $0, $0;
    daddu      $4, $17, $0;
    jal        DoubleCmp_13b948;
    nop;
    daddu      $4, $17, $0;
    ori        $5, $0, 0xF7C0;
    dsll32     $5, $5, 14;
    bltz       $2, L0013ADC8;
    daddu     $2, $0, $0;
    jal        dpmul;
    nop;
    daddu      $4, $2, $0;
    jal        DoubleToUInt_13bb78;
    nop;
    dsll32     $16, $2, 0;
    andi       $2, $16, 0x1;
    dsrl       $4, $16, 1;
    bltz       $16, L0013AD38;
    or        $4, $2, $4;
    jal        S64ToDouble_13a998;
    daddu     $4, $16, $0;
    b          L0013AD50;
    nop;
    nop;
  L0013AD38:
    jal        S64ToDouble_13a998;
    nop;
    daddu      $4, $2, $0;
    daddu      $5, $4, $0;
    jal        dpadd;
    nop;
  L0013AD50:
    daddu      $4, $17, $0;
    daddu      $5, $2, $0;
    jal        dpsub;
    nop;
    daddu      $18, $0, $0;
    daddu      $17, $2, $0;
    daddu      $5, $18, $0;
    daddu      $4, $17, $0;
    jal        DoubleCmp_13b948;
    nop;
    daddu      $4, $17, $0;
    daddu      $5, $17, $0;
    bgez       $2, L0013ADB0;
    nop;
    daddu      $4, $18, $0;
    jal        dpsub;
    nop;
    daddu      $4, $2, $0;
    jal        DoubleToUInt_13bb78;
    nop;
    dsll32     $2, $2, 0;
    dsrl32     $2, $2, 0;
    b          L0013ADC4;
    dsubu     $16, $16, $2;
  L0013ADB0:
    jal        DoubleToUInt_13bb78;
    nop;
    dsll32     $2, $2, 0;
    dsrl32     $2, $2, 0;
    daddu      $16, $16, $2;
  L0013ADC4:
    daddu      $2, $16, $0;
  L0013ADC8:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

