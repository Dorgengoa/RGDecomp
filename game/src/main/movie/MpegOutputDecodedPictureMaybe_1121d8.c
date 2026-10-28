#include "types.h"

extern void MpegOutputFrameMaybe_111a38(void);
extern void MpegOutputFieldPairMaybe_111cf8(void);

asm void MpegOutputDecodedPictureMaybe_1121d8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $7, $5, $0;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    beqz       $6, L00112244;
    daddu     $16, $4, $0;
    lw         $2, 0x184($16);
    addiu      $3, $0, 0x3;
    bne        $2, $3, L00112220;
    lw        $2, 0x160($16);
    bnel       $2, $3, L0011220C;
    lw        $5, 0x1C8($16);
    lw         $5, 0x1D4($16);
  L0011220C:
    addiu      $6, $7, -0x1;
    jal        MpegOutputFrameMaybe_111a38;
    daddu     $4, $16, $0;
    b          L00112248;
    lw        $3, 0x108($16);
  L00112220:
    bnel       $2, $3, L00112234;
    lw        $5, 0x1D8($16);
    lw         $5, 0x1E4($16);
    b          L00112238;
    lw        $6, 0x1F4($16);
  L00112234:
    lw         $6, 0x1E8($16);
  L00112238:
    addiu      $7, $7, -0x1;
    jal        MpegOutputFieldPairMaybe_111cf8;
    daddu     $4, $16, $0;
  L00112244:
    lw         $3, 0x108($16);
  L00112248:
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0011225C;
    ld        $31, 0x10($29);
    addiu      $2, $0, 0x2;
    sw         $2, 0x108($16);
  L0011225C:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
