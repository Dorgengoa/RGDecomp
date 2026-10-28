#include "types.h"

extern void MpegReportError_115a90(void);

asm void MpegSetupBufferType_1103d8(void)
{
    .set noreorder;
    lui        $5, (0x10002010 >> 16);
    lui        $3, (0xFF7FFFFF >> 16);
    ori        $5, $5, (0x10002010 & 0xFFFF);
    ori        $3, $3, (0xFF7FFFFF & 0xFFFF);
    lw         $2, 0x0($5);
    lui        $6, (0x800000 >> 16);
    daddu      $7, $4, $0;
    and        $2, $2, $3;
    or         $2, $2, $6;
    sw         $2, 0x0($5);
    lw         $3, 0x87C($7);
    bnez       $3, L0011044C;
    addiu     $2, $0, 0x1;
    lui        $2, (0x70003600 >> 16);
    lui        $3, (0x70001800 >> 16);
    lui        $4, (0x70001B00 >> 16);
    lui        $5, (0x70003300 >> 16);
    lui        $6, (0x70000000 >> 16);
    ori        $2, $2, (0x70003600 & 0xFFFF);
    ori        $3, $3, (0x70001800 & 0xFFFF);
    ori        $4, $4, (0x70001B00 & 0xFFFF);
    ori        $5, $5, (0x70003300 & 0xFFFF);
    sw         $2, 0x830($7);
    sw         $6, 0x5A0($7);
    sw         $3, 0x5A4($7);
    sw         $4, 0x6E0($7);
    sw         $5, 0x6E4($7);
    jr         $31;
    sw        $0, 0x820($7);
  L0011044C:
    bne        $3, $2, L00110498;
    lui       $5, 0x45;
    lui        $2, (0xFFFFFFF >> 16);
    addiu      $4, $7, 0x880;
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    addiu      $3, $7, 0xB80;
    and        $3, $3, $2;
    and        $4, $4, $2;
    lui        $5, (0x30000000 >> 16);
    addiu      $2, $7, 0xE80;
    or         $3, $3, $5;
    or         $4, $4, $5;
    sw         $2, 0x830($7);
    sw         $4, 0x5A4($7);
    sw         $3, 0x6E4($7);
    sw         $0, 0x820($7);
    sw         $0, 0x5A0($7);
    jr         $31;
    sw        $0, 0x6E0($7);
  L00110498:
    daddu      $4, $7, $0;
    j          MpegReportError_115a90;
    addiu     $5, $5, 0x63F0;
}
