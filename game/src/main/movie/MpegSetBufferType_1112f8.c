#include "types.h"

extern void MpegSetupBufferType_1103d8(void);

asm void MpegSetBufferType_1112f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sltiu      $2, $5, 0x2;
    sd         $31, 0x0($29);
    bnez       $2, L00111314;
    lw        $4, 0x40($4);
    b          L00111320;
    addiu     $2, $0, -0x1;
  L00111314:
    jal        MpegSetupBufferType_1103d8;
    sw        $5, 0x87C($4);
    addiu      $2, $0, 0x1;
  L00111320:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
