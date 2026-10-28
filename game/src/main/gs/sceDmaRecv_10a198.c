#include "types.h"

extern void DmaWaitChannelIdle_109bb8(void);

asm void sceDmaRecv_10a198(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        DmaWaitChannelIdle_109bb8;
    daddu     $16, $4, $0;
    lw         $2, 0x0($16);
    addiu      $3, $0, -0xD;
    addiu      $4, $0, -0x2;
    sw         $0, 0x20($16);
    and        $2, $2, $3;
    ld         $31, 0x10($29);
    ori        $2, $2, 0x4;
    and        $2, $2, $4;
    ori        $2, $2, 0x100;
    sw         $2, 0x0($16);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

