#include "types.h"

extern void UDivDi3_139eb0(void);

asm void TimerBusClock2USec_122098(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $18, 0x20($29);
    daddu      $16, $5, $0;
    sd         $31, 0x30($29);
    daddu      $18, $6, $0;
    jal        UDivDi3_139eb0;
    lui       $5, (0x8CA0000 >> 16);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    bnel       $16, $0, L001220D0;
    sw        $2, 0x0($16);
  L001220D0:
    beqz       $18, L00122128;
    lui       $3, (0x8CA0000 >> 16);
    lui        $5, (0x8CA0000 >> 16);
    multu      $2, $3;
    mflo       $6;
    mfhi       $3;
    dsll32     $6, $6, 0;
    dsll32     $3, $3, 0;
    dsrl32     $6, $6, 0;
    or         $3, $3, $6;
    dsubu      $3, $17, $3;
    dsll       $2, $3, 5;
    dsubu      $2, $2, $3;
    dsll       $4, $2, 6;
    dsubu      $4, $4, $2;
    dsll       $4, $4, 3;
    daddu      $4, $4, $3;
    jal        UDivDi3_139eb0;
    dsll      $4, $4, 6;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    sw         $2, 0x0($18);
  L00122128:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
