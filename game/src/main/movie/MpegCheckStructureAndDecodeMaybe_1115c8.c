#include "types.h"

extern void MpegReportError_115a90(void);
extern void MpegDecodePictureBodyMaybe_10c798(void);

asm void MpegCheckStructureAndDecodeMaybe_1115c8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $2, $0, 0x3;
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    daddu      $16, $4, $0;
    sd         $17, 0x10($29);
    lw         $3, 0x184($16);
    bne        $3, $2, L00111610;
    addiu     $2, $0, 0x2;
    lw         $2, 0x130($16);
    beqz       $2, L00111610;
    addiu     $2, $0, 0x2;
    lui        $5, 0x45;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6538;
    sw         $0, 0x130($16);
    lw         $3, 0x184($16);
    addiu      $2, $0, 0x2;
  L00111610:
    beq        $3, $2, L0011164C;
    slti      $2, $3, 0x3;
    beqz       $2, L00111630;
    addiu     $2, $0, 0x1;
    beq        $3, $2, L00111644;
    lui       $5, 0x45;
    b          L00111658;
    lw        $17, 0x1D0($16);
  L00111630:
    addiu      $2, $0, 0x3;
    bne        $3, $2, L00111654;
    lui       $5, 0x45;
    b          L00111664;
    lw        $17, 0x1D0($16);
  L00111644:
    b          L00111664;
    lw        $17, 0x1E0($16);
  L0011164C:
    b          L00111664;
    lw        $17, 0x1F0($16);
  L00111654:
    lw         $17, 0x1D0($16);
  L00111658:
    addiu      $5, $5, 0x6558;
    jal        MpegReportError_115a90;
    daddu     $4, $16, $0;
  L00111664:
    jal        MpegDecodePictureBodyMaybe_10c798;
    daddu     $4, $16, $0;
    daddu      $3, $2, $0;
    beqz       $3, L0011167C;
    addiu     $2, $0, 0x1;
    sw         $2, 0x28($17);
  L0011167C:
    ld         $31, 0x20($29);
    daddu      $2, $3, $0;
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
