#include "types.h"

extern void MpegGetPictureImpl_1108a8(void);

asm void MpegGetPicture_111148(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, (0xFFFFFFF >> 16);
    sd         $31, 0x0($29);
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    and        $5, $5, $2;
    lui        $3, (0x20000000 >> 16);
    lw         $7, 0x40($4);
    or         $5, $5, $3;
    addiu      $2, $0, 0x1;
    sw         $2, 0xC4($7);
    sw         $5, 0xEC($7);
    sw         $6, 0xF8($7);
    sw         $0, 0xF0($7);
    jal        MpegGetPictureImpl_1108a8;
    sw        $0, 0xF4($7);
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
