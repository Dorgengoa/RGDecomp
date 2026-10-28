#include "types.h"

extern void MpegDecodeFieldPicture_110e88(void);
extern void MpegDecodeFramePicture_110d18(void);

asm void MpegDecodePicture_111430(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $7, $4, $0;
    sd         $31, 0x0($29);
    addiu      $3, $0, 0x3;
    lw         $4, 0x40($7);
    lw         $2, 0x184($4);
    beq        $2, $3, L00111460;
    nop;
    jal        MpegDecodeFieldPicture_110e88;
    daddu     $4, $7, $0;
    b          L0011146C;
    ld        $31, 0x0($29);
  L00111460:
    jal        MpegDecodeFramePicture_110d18;
    daddu     $4, $7, $0;
    ld         $31, 0x0($29);
  L0011146C:
    jr         $31;
    addiu     $29, $29, 0x10;
}
