#include "types.h"

extern void UDivDi3_139eb0(void);

asm void TimerUSec2BusClock_122140(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    lui        $2, (0x8CA0000 >> 16);
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x10($29);
    daddu      $4, $5, $0;
    multu1     $0, $16, $2;
    multu      $4, $2;
    lui        $5, (0xF4240 >> 16);
    ori        $5, $5, (0xF4240 & 0xFFFF);
    mfhi1      $16;
    mflo       $6;
    dsll32     $16, $16, 0;
    dsll32     $6, $6, 0;
    mfhi       $4;
    dsrl32     $6, $6, 0;
    dsll32     $4, $4, 0;
    or         $4, $4, $6;
    mflo1      $6;
    dsll32     $6, $6, 0;
    dsrl32     $6, $6, 0;
    jal        UDivDi3_139eb0;
    or        $16, $16, $6;
    daddu      $2, $16, $2;
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
