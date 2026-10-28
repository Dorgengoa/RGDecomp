#include "types.h"

extern void DmaAddrFromSpr_109cb0(void);
extern void DmaWaitChannelIdle_109bb8(void);

asm void sceDmaSend_10a040(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    jal        DmaAddrFromSpr_109cb0;
    daddu     $4, $5, $0;
    daddu      $17, $2, $0;
    jal        DmaWaitChannelIdle_109bb8;
    daddu     $4, $16, $0;
    lui        $2, (0xFFFFFFFF >> 16);
    lw         $3, 0x30($16);
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
    bnel       $3, $2, L0010A07C;
    sw        $17, 0x30($16);
  L0010A07C:
    lw         $2, 0x0($16);
    addiu      $3, $0, -0xD;
    sw         $0, 0x20($16);
    and        $2, $2, $3;
    ld         $31, 0x20($29);
    ori        $2, $2, 0x105;
    ld         $17, 0x10($29);
    sw         $2, 0x0($16);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

