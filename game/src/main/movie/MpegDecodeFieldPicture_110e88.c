#include "types.h"

extern void MpegPrepareDecodeBufferMaybe_110a60(void);
extern void MpegCheckStructureAndDecodeMaybe_1115c8(void);
extern void MpegNextPictureMaybe_110008(void);
extern void MpegOutputPictureMaybe_112118(void);
extern void MpegOutputDecodedPictureMaybe_1121d8(void);

asm void MpegDecodeFieldPicture_110e88(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    addiu      $2, $0, -0x1;
    sd         $19, 0x50($29);
    sd         $17, 0x30($29);
    daddu      $19, $0, $0;
    sd         $31, 0x70($29);
    daddu      $17, $4, $0;
    sd         $20, 0x60($29);
    sd         $18, 0x40($29);
    sd         $16, 0x20($29);
    lw         $16, 0x40($17);
    beq        $6, $2, L00110EC8;
    sw        $0, 0x130($16);
    slt        $2, $5, $6;
    beql       $2, $0, L00110ED0;
    lw        $2, 0x8($16);
  L00110EC8:
    addiu      $19, $0, 0x1;
    lw         $2, 0x8($16);
  L00110ED0:
    bnez       $2, L00110EE4;
    daddu     $4, $16, $0;
    sw         $0, 0x8($17);
    addiu      $2, $0, 0x1;
    sw         $2, 0x8($16);
  L00110EE4:
    jal        MpegPrepareDecodeBufferMaybe_110a60;
    daddu     $5, $0, $0;
    beql       $2, $0, L00110F08;
    lw        $2, 0x878($16);
    beql       $19, $0, L00110F08;
    lw        $2, 0x878($16);
    jal        MpegCheckStructureAndDecodeMaybe_1115c8;
    daddu     $4, $16, $0;
    lw         $2, 0x878($16);
  L00110F08:
    bnez       $2, L0011102C;
    daddu     $2, $0, $0;
    addiu      $18, $0, 0x1;
    daddu      $4, $16, $0;
    jal        MpegNextPictureMaybe_110008;
    sw        $18, 0x130($16);
    bnel       $2, $0, L00110F3C;
    lw        $2, 0xE8($16);
    jal        MpegOutputPictureMaybe_112118;
    daddu     $4, $17, $0;
    sw         $18, 0x0($16);
    b          L0011102C;
    daddu     $2, $0, $0;
  L00110F3C:
    addiu      $3, $0, 0x2;
    lw         $4, 0x184($16);
    xori       $2, $2, 0x1;
    movn       $3, $18, $2;
    bne        $4, $3, L0011102C;
    addiu     $2, $0, -0x1;
    daddu      $4, $16, $0;
    jal        MpegPrepareDecodeBufferMaybe_110a60;
    addiu     $5, $0, 0x1;
    daddu      $3, $0, $0;
    movn       $3, $18, $2;
    beqz       $3, L00110F84;
    daddu     $20, $0, $0;
    beql       $19, $0, L00110F88;
    lw        $2, 0x878($16);
    jal        MpegCheckStructureAndDecodeMaybe_1115c8;
    daddu     $4, $16, $0;
    movn       $20, $18, $2;
  L00110F84:
    lw         $2, 0x878($16);
  L00110F88:
    bnez       $2, L0011102C;
    daddu     $2, $0, $0;
    lw         $5, 0x128($16);
    daddu      $4, $16, $0;
    jal        MpegOutputDecodedPictureMaybe_1121d8;
    lw        $6, 0x4($16);
    lw         $2, 0x128($16);
    lw         $3, 0xC0($16);
    sw         $0, 0x130($16);
    subu       $2, $2, $3;
    sw         $2, 0x8($17);
    lw         $3, 0x128($16);
    lw         $2, 0x4($16);
    addiu      $3, $3, 0x1;
    addiu      $2, $2, 0x1;
    sw         $3, 0x128($16);
    bnez       $19, L00111028;
    sw        $2, 0x4($16);
    addiu      $2, $0, 0x1;
    beqz       $17, L00111028;
    sw        $2, 0x0($29);
    lw         $6, 0x40($17);
    beqz       $6, L0011102C;
    daddu     $2, $20, $0;
    lw         $7, 0x18($6);
    beqz       $7, L00111030;
    ld        $31, 0x70($29);
    lw         $2, 0x20($6);
    daddu      $16, $28, $0;
    daddu      $28, $2, $0;
    lw         $3, 0x0($29);
    addiu      $2, $0, 0xC;
    daddu      $4, $17, $0;
    daddu      $5, $29, $0;
    mult       $8, $3, $2;
    addu       $3, $8, $6;
    jalr $31, $7;
    lw        $6, 0x10($3);
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
  L00111028:
    daddu      $2, $20, $0;
  L0011102C:
    ld         $31, 0x70($29);
  L00111030:
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

