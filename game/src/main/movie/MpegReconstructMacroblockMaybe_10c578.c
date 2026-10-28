#include "types.h"

extern void MpegReportError_115a90(void);
extern void MpegClampPackBlock_10e088(void);
extern void MpegAddBlockClampPack_10df98(void);

asm void MpegReconstructMacroblockMaybe_10c578(void)
{
    .set noreorder;
    addiu      $29, $29, -0xB0;
    addiu      $2, $0, 0x140;
    sw         $5, 0x0($29);
    sd         $20, 0x50($29);
    mult       $5, $5, $2;
    sd         $31, 0xA0($29);
    sd         $30, 0x90($29);
    daddu      $20, $4, $0;
    sd         $23, 0x80($29);
    sd         $22, 0x70($29);
    sd         $21, 0x60($29);
    addu       $2, $20, $5;
    sd         $19, 0x40($29);
    sd         $18, 0x30($29);
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    lw         $3, 0x6D8($2);
    beqz       $3, L0010C65C;
    addiu     $2, $20, 0x6CC;
    sw         $2, 0x4($29);
    addu       $2, $2, $5;
    lw         $3, 0x0($2);
    blez       $3, L0010C66C;
    daddu     $21, $0, $0;
    addiu      $3, $20, 0x6D0;
    addiu      $23, $20, 0x5C8;
    sw         $3, 0x8($29);
    addiu      $22, $20, 0x5D8;
    addiu      $30, $20, 0x6C8;
    lw         $2, 0x0($29);
  L0010C5F0:
    addiu      $17, $0, 0x140;
    addiu      $19, $0, 0x1C;
    sll        $16, $21, 2;
    mult       $17, $2, $17;
    mult1      $19, $21, $19;
    addiu      $21, $21, 0x1;
    addu       $16, $16, $17;
    addiu      $18, $17, 0x5A0;
    addu       $2, $23, $16;
    addu       $18, $20, $18;
    addiu      $4, $19, 0x48;
    lw         $3, 0x0($2);
    jalr $31, $3;
    addu      $4, $18, $4;
    addu       $16, $22, $16;
    addiu      $19, $19, 0xB8;
    lw         $2, 0x0($16);
    jalr $31, $2;
    addu      $4, $18, $19;
    lw         $3, 0x4($29);
    addu       $17, $3, $17;
    lw         $2, 0x0($17);
    slt        $2, $21, $2;
    bnez       $2, L0010C5F0;
    lw        $2, 0x0($29);
    b          L0010C67C;
    lw        $3, 0x0($29);
  L0010C65C:
    addiu      $2, $20, 0x6D0;
    addiu      $30, $20, 0x6C8;
    b          L0010C678;
    sw        $2, 0x8($29);
  L0010C66C:
    addiu      $3, $20, 0x6D0;
    addiu      $30, $20, 0x6C8;
    sw         $3, 0x8($29);
  L0010C678:
    lw         $3, 0x0($29);
  L0010C67C:
    addiu      $2, $0, 0x140;
    mult       $4, $3, $2;
    lw         $2, 0x8($29);
    addu       $3, $2, $4;
    lw         $2, 0x0($3);
    beqz       $2, L0010C6B0;
    addu      $2, $20, $4;
    lw         $3, 0x6DC($2);
    beqz       $3, L0010C6B0;
    lui       $5, 0x45;
    daddu      $4, $20, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6118;
  L0010C6B0:
    lw         $3, 0x0($29);
    addiu      $2, $0, 0x140;
    mult       $5, $3, $2;
    lw         $2, 0x8($29);
    addu       $3, $2, $5;
    lw         $2, 0x0($3);
    beqz       $2, L0010C710;
    addu      $2, $20, $5;
    addu       $2, $30, $5;
    addu       $3, $20, $5;
    lw         $4, 0x0($2);
    lw         $5, 0x5A4($3);
    ld         $31, 0xA0($29);
    ld         $30, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    j          MpegClampPackBlock_10e088;
    addiu     $29, $29, 0xB0;
  L0010C710:
    lw         $3, 0x6DC($2);
    beqz       $3, L0010C754;
    addu      $2, $30, $5;
    ld         $31, 0xA0($29);
    lw         $5, 0x830($20);
    lw         $4, 0x0($2);
    ld         $30, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    j          MpegClampPackBlock_10e088;
    addiu     $29, $29, 0xB0;
  L0010C754:
    addu       $3, $20, $5;
    lw         $5, 0x830($20);
    lw         $4, 0x0($2);
    lw         $6, 0x5A4($3);
    ld         $31, 0xA0($29);
    ld         $30, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    j          MpegAddBlockClampPack_10df98;
    addiu     $29, $29, 0xB0;
}

