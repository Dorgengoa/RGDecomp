#include "types.h"

extern void MpegPrepareDecodeBufferMaybe_110a60(void);
extern void MpegCheckStructureAndDecodeMaybe_1115c8(void);
extern void MpegOutputDecodedPictureMaybe_1121d8(void);

asm void MpegDecodeFramePicture_110d18(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    addiu      $2, $0, -0x1;
    sd         $18, 0x40($29);
    sd         $16, 0x20($29);
    daddu      $18, $4, $0;
    sd         $31, 0x60($29);
    daddu      $16, $0, $0;
    sd         $19, 0x50($29);
    sd         $17, 0x30($29);
    beq        $6, $2, L00110D50;
    lw        $17, 0x40($18);
    slt        $2, $5, $6;
    beqz       $2, L00110D8C;
    daddu     $4, $17, $0;
  L00110D50:
    lw         $2, 0x8($17);
    bnez       $2, L00110D68;
    daddu     $4, $17, $0;
    sw         $0, 0x8($18);
    addiu      $2, $0, 0x1;
    sw         $2, 0x8($17);
  L00110D68:
    jal        MpegPrepareDecodeBufferMaybe_110a60;
    daddu     $5, $0, $0;
    beqz       $2, L00110D84;
    daddu     $3, $0, $0;
    jal        MpegCheckStructureAndDecodeMaybe_1115c8;
    daddu     $4, $17, $0;
    sltu       $3, $0, $2;
  L00110D84:
    b          L00110DF4;
    daddu     $19, $3, $0;
  L00110D8C:
    jal        MpegPrepareDecodeBufferMaybe_110a60;
    daddu     $5, $0, $0;
    addiu      $3, $0, 0x1;
    daddu      $19, $2, $0;
    beqz       $18, L00110DF0;
    sw        $3, 0x0($29);
    lw         $6, 0x40($18);
    beqz       $6, L00110DF4;
    addiu     $16, $0, 0x1;
    lw         $7, 0x18($6);
    beql       $7, $0, L00110DF8;
    lw        $2, 0x878($17);
    lw         $2, 0x20($6);
    daddu      $16, $28, $0;
    daddu      $28, $2, $0;
    lw         $3, 0x0($29);
    addiu      $2, $0, 0xC;
    daddu      $4, $18, $0;
    daddu      $5, $29, $0;
    mult       $8, $3, $2;
    addu       $3, $8, $6;
    jalr $31, $7;
    lw        $6, 0x10($3);
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
  L00110DF0:
    addiu      $16, $0, 0x1;
  L00110DF4:
    lw         $2, 0x878($17);
  L00110DF8:
    bnez       $2, L00110E6C;
    daddu     $2, $0, $0;
    lw         $5, 0x128($17);
    daddu      $4, $17, $0;
    jal        MpegOutputDecodedPictureMaybe_1121d8;
    lw        $6, 0x4($17);
    lw         $3, 0x184($17);
    addiu      $2, $0, 0x3;
    beql       $3, $2, L00110E38;
    lw        $3, 0xC0($17);
    bnel       $16, $0, L00110E38;
    lw        $3, 0xC0($17);
    lw         $2, 0x130($17);
    sltiu      $2, $2, 0x1;
    sw         $2, 0x130($17);
    lw         $3, 0xC0($17);
  L00110E38:
    lw         $2, 0x128($17);
    subu       $2, $2, $3;
    sw         $2, 0x8($18);
    lw         $3, 0x130($17);
    bnez       $3, L00110E6C;
    daddu     $2, $19, $0;
    lw         $2, 0x128($17);
    lw         $3, 0x4($17);
    addiu      $2, $2, 0x1;
    addiu      $3, $3, 0x1;
    sw         $2, 0x128($17);
    sw         $3, 0x4($17);
    daddu      $2, $19, $0;
  L00110E6C:
    ld         $31, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

