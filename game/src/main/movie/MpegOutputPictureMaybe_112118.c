#include "types.h"

extern void MpegReportError_115a90(void);
extern void MpegOutputFrameMaybe_111a38(void);
extern void MpegOutputFieldPairMaybe_111cf8(void);

asm void MpegOutputPictureMaybe_112118(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    lw         $16, 0x40($17);
    lw         $2, 0x4($16);
    beqz       $2, L001121C0;
    daddu     $4, $0, $0;
    lw         $2, 0x8($16);
    beqz       $2, L001121C4;
    ld        $31, 0x20($29);
    lw         $2, 0x130($16);
    beqz       $2, L0011216C;
    lw        $6, 0x128($16);
    lui        $5, 0x45;
    daddu      $4, $16, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x65C8;
    b          L001121A8;
    lw        $2, 0x128($16);
  L0011216C:
    lw         $3, 0x184($16);
    addiu      $2, $0, 0x3;
    bne        $3, $2, L00112194;
    addiu     $7, $6, -0x1;
    lw         $5, 0x1CC($16);
    addiu      $6, $6, -0x1;
    jal        MpegOutputFrameMaybe_111a38;
    daddu     $4, $16, $0;
    b          L001121A8;
    lw        $2, 0x128($16);
  L00112194:
    lw         $5, 0x1DC($16);
    lw         $6, 0x1EC($16);
    jal        MpegOutputFieldPairMaybe_111cf8;
    daddu     $4, $16, $0;
    lw         $2, 0x128($16);
  L001121A8:
    addiu      $4, $0, 0x1;
    lw         $3, 0xC0($16);
    sw         $0, 0x130($16);
    subu       $2, $2, $3;
    sw         $2, 0x8($17);
    sw         $0, 0x4($16);
  L001121C0:
    ld         $31, 0x20($29);
  L001121C4:
    daddu      $2, $4, $0;
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
