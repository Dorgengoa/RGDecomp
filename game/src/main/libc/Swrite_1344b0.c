#include "types.h"

extern void LseekR_1309f0(void);
extern void WriteR_138fa0(void);

asm void Swrite_1344b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sd         $18, 0x10($29);
    daddu      $18, $6, $0;
    sd         $31, 0x18($29);
    lhu        $2, 0xC($16);
    andi       $2, $2, 0x100;
    beqz       $2, L001344F0;
    daddu     $6, $0, $0;
    lw         $4, 0x54($16);
    addiu      $7, $0, 0x2;
    jal        LseekR_1309f0;
    lh        $5, 0xE($16);
  L001344F0:
    lhu        $2, 0xC($16);
    daddu      $6, $17, $0;
    lh         $5, 0xE($16);
    daddu      $7, $18, $0;
    andi       $2, $2, 0xEFFF;
    lw         $4, 0x54($16);
    jal        WriteR_138fa0;
    sh        $2, 0xC($16);
    ld         $16, 0x0($29);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

