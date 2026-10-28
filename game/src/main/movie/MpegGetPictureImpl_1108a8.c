#include "types.h"

extern void MpegReportErrorFmt_115ae8(void);
extern void scePrintf_119288(void);
extern void MpegNextPictureMaybe_110008(void);
extern void MpegOutputPictureMaybe_112118(void);
extern void MpegDecodePicture_111430(void);

asm void MpegGetPictureImpl_1108a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    daddu      $19, $0, $0;
    sd         $17, 0x10($29);
    addiu      $18, $0, 0x1;
    sd         $31, 0x40($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    lw         $16, 0x40($17);
    lw         $6, 0xEC($16);
    andi       $2, $6, 0x3F;
    beqz       $2, L001108F8;
    sw        $0, 0x0($16);
    lui        $5, 0x45;
    daddu      $4, $16, $0;
    jal        MpegReportErrorFmt_115ae8;
    addiu     $5, $5, 0x6480;
    b          L00110A40;
    addiu     $2, $0, -0x1;
  L001108F8:
    lw         $2, 0x878($16);
    beqz       $2, L00110924;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x64C0;
    b          L00110A40;
    addiu     $2, $0, -0x1;
  L00110914:
    jal        scePrintf_119288;
    addiu     $4, $4, 0x6500;
    b          L00110A40;
    addiu     $2, $0, -0x1;
  L00110924:
    sw         $0, 0x834($16);
    addiu      $2, $0, -0x1;
    nop;
  L00110930:
    beq        $19, $2, L00110970;
    sltiu     $2, $18, 0x5;
  L00110938:
    jal        MpegNextPictureMaybe_110008;
    daddu     $4, $16, $0;
    daddu      $18, $2, $0;
    bltz       $18, L00110A40;
    addiu     $2, $0, -0x1;
    beqz       $18, L00110970;
    sltiu     $2, $18, 0x5;
    lw         $3, 0x184($16);
    lw         $2, 0xE8($16);
    beq        $3, $2, L00110970;
    sltiu     $2, $18, 0x5;
    lw         $2, 0x858($16);
    bnez       $2, L00110938;
    sltiu     $2, $18, 0x5;
  L00110970:
    beqz       $2, L00110A18;
    lui       $2, 0x45;
    sll        $3, $18, 2;
    addiu      $2, $2, 0x6520;
    addu       $3, $3, $2;
    lw         $4, 0x0($3);
    jr         $4;
    nop;
    jal        MpegOutputPictureMaybe_112118;
    daddu     $4, $17, $0;
    addiu      $3, $0, 0x1;
    b          L00110A18;
    sw        $3, 0x0($16);
    sw         $0, 0xBC($16);
    daddu      $4, $17, $0;
    sw         $0, 0xB8($16);
    daddu      $5, $0, $0;
    sw         $0, 0xB4($16);
    jal        MpegDecodePicture_111430;
    lw        $6, 0xA8($16);
    lw         $3, 0xB4($16);
    daddu      $19, $2, $0;
    addiu      $3, $3, 0x1;
    b          L00110A18;
    sw        $3, 0xB4($16);
    lw         $5, 0xB8($16);
    daddu      $4, $17, $0;
    jal        MpegDecodePicture_111430;
    lw        $6, 0xAC($16);
    lw         $3, 0xB8($16);
    daddu      $19, $2, $0;
    addiu      $3, $3, 0x1;
    b          L00110A18;
    sw        $3, 0xB8($16);
    lw         $5, 0xBC($16);
    daddu      $4, $17, $0;
    jal        MpegDecodePicture_111430;
    lw        $6, 0xB0($16);
    lw         $3, 0xBC($16);
    daddu      $19, $2, $0;
    addiu      $3, $3, 0x1;
    sw         $3, 0xBC($16);
  L00110A18:
    lw         $2, 0x878($16);
    bnez       $2, L00110914;
    lui       $4, 0x45;
    lw         $2, 0x834($16);
    bnez       $2, L00110A40;
    addiu     $2, $0, 0x1;
    lw         $2, 0x0($16);
    beqz       $2, L00110930;
    addiu     $2, $0, -0x1;
    addiu      $2, $0, 0x1;
  L00110A40:
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
