#include "types.h"

extern void IpuGetBits_10dc88(void);
extern void MpegReportError_115a90(void);

asm void MpegParseSequenceExt_10f9a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    lui        $6, (0x10002010 >> 16);
    sd         $17, 0x10($29);
    ori        $6, $6, (0x10002010 & 0xFFFF);
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $21, 0x50($29);
    addiu      $16, $0, 0x1;
    sd         $20, 0x40($29);
    lui        $2, (0xFF7FFFFF >> 16);
    sd         $19, 0x30($29);
    ori        $2, $2, (0xFF7FFFFF & 0xFFFF);
    sd         $18, 0x20($29);
    sd         $31, 0x60($29);
    addiu      $5, $0, 0x1C;
    sw         $16, 0x858($17);
    lw         $3, 0x0($6);
    and        $3, $3, $2;
    jal        IpuGetBits_10dc88;
    sw        $3, 0x0($6);
    daddu      $18, $2, $0;
    srl        $3, $18, 1;
    srl        $2, $18, 17;
    andi       $21, $3, 0xFFF;
    andi       $2, $2, 0x3;
    srl        $4, $18, 13;
    srl        $3, $18, 15;
    andi       $20, $4, 0x3;
    andi       $19, $3, 0x3;
    beq        $2, $16, L0010FA34;
    sw        $2, 0x150($17);
    lui        $5, 0x45;
    daddu      $4, $17, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6260;
  L0010FA34:
    srl        $2, $18, 19;
    daddu      $4, $17, $0;
    andi       $2, $2, 0x1;
    addiu      $5, $0, 0x10;
    sw         $2, 0x14C($17);
    jal        IpuGetBits_10dc88;
    srl       $16, $18, 20;
    srl        $18, $2, 8;
    addiu      $2, $0, 0x48;
    beq        $16, $2, L0010FA7C;
    addiu     $2, $0, 0x58;
    beq        $16, $2, L0010FA7C;
    addiu     $2, $0, 0x44;
    beq        $16, $2, L0010FA7C;
    lui       $5, 0x45;
    daddu      $4, $17, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6288;
  L0010FA7C:
    lw         $4, 0x134($17);
    sll        $8, $21, 18;
    lw         $3, 0x138($17);
    sll        $9, $18, 10;
    lw         $6, 0x144($17);
    sll        $7, $19, 12;
    lw         $2, 0x148($17);
    sll        $5, $20, 12;
    andi       $4, $4, 0xFFF;
    andi       $3, $3, 0xFFF;
    or         $7, $7, $4;
    or         $5, $5, $3;
    addu       $6, $6, $8;
    addu       $2, $2, $9;
    sw         $2, 0x148($17);
    sw         $7, 0x134($17);
    sw         $5, 0x138($17);
    sw         $6, 0x144($17);
    ld         $31, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

