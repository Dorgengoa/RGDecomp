#include "types.h"

extern void MpegResetHwMaybe_1107e0(void);

asm void MpegReset_1111e8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $2, $4, $0;
    sd         $31, 0x10($29);
    addiu      $3, $0, -0x1;
    sd         $16, 0x0($29);
    lw         $16, 0x40($2);
    sw         $0, 0x878($16);
    daddu      $4, $16, $0;
    sw         $0, 0x0($16);
    sw         $0, 0x4($16);
    sw         $0, 0x8($16);
    sw         $0, 0x8($2);
    sw         $0, 0xC0($16);
    jal        MpegResetHwMaybe_1107e0;
    sw        $3, 0x98($16);
    sw         $0, 0x858($16);
    lui        $5, (0x10002010 >> 16);
    sw         $0, 0x128($16);
    ori        $5, $5, (0x10002010 & 0xFFFF);
    lui        $4, (0xFF7FFFFF >> 16);
    lui        $6, (0x800000 >> 16);
    lw         $3, 0x0($5);
    ori        $4, $4, (0xFF7FFFFF & 0xFFFF);
    ld         $31, 0x10($29);
    addiu      $2, $0, 0x1;
    and        $3, $3, $4;
    ld         $16, 0x0($29);
    or         $3, $3, $6;
    sw         $3, 0x0($5);
    jr         $31;
    addiu     $29, $29, 0x20;
}
