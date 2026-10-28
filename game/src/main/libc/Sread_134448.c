#include "types.h"

extern void ReadR_133778(void);

asm void Sread_134448(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $7, $6, $0;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x8($29);
    daddu      $6, $5, $0;
    lw         $4, 0x54($16);
    jal        ReadR_133778;
    lh        $5, 0xE($16);
    dsll32     $4, $2, 0;
    dsra32     $4, $4, 0;
    bltz       $4, L00134490;
    daddu     $2, $4, $0;
    lw         $3, 0x50($16);
    addu       $3, $3, $4;
    b          L0013449C;
    sw        $3, 0x50($16);
    nop;
  L00134490:
    lhu        $3, 0xC($16);
    andi       $3, $3, 0xEFFF;
    sh         $3, 0xC($16);
  L0013449C:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

