#include "types.h"

extern void MpegReportError_115a90(void);

asm void MpegSkippedMacroblock_10ded8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $3, $0, 0x140;
    sd         $16, 0x0($29);
    addiu      $9, $0, 0x1;
    sd         $31, 0x10($29);
    daddu      $16, $8, $0;
    addiu      $8, $0, 0x2;
    lw         $2, 0x820($4);
    mult       $10, $2, $3;
    addu       $2, $10, $4;
    sw         $9, 0x6DC($2);
    sw         $9, 0x1C0($4);
    lw         $2, 0x160($4);
    bnel       $2, $8, L0010DF28;
    lw        $3, 0x184($4);
    sw         $0, 0x0($5);
    sw         $0, 0x14($5);
    sw         $0, 0x10($5);
    sw         $0, 0x4($5);
    lw         $3, 0x184($4);
  L0010DF28:
    addiu      $2, $0, 0x3;
    bnel       $3, $2, L0010DF3C;
    sw        $9, 0x0($6);
    b          L0010DF50;
    sw        $8, 0x0($6);
  L0010DF3C:
    lw         $2, 0x184($4);
    xori       $2, $2, 0x2;
    sltiu      $2, $2, 0x1;
    sw         $2, 0x0($7);
    sw         $2, 0x4($7);
  L0010DF50:
    lw         $3, 0x160($4);
    addiu      $2, $0, 0x1;
    bnel       $3, $2, L0010DF74;
    lw        $3, 0x0($16);
    lui        $5, 0x45;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6170;
    daddu      $9, $0, $0;
    lw         $3, 0x0($16);
  L0010DF74:
    addiu      $4, $0, -0x2;
    ld         $31, 0x10($29);
    daddu      $2, $9, $0;
    and        $3, $3, $4;
    sw         $3, 0x0($16);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

