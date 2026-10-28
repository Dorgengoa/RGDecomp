#include "types.h"

extern void MpegGetPictureImpl_1108a8(void);

asm void MpegGetPictureRaw8Xy_1114d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, (0xFFFFFFF >> 16);
    sd         $31, 0x0($29);
    mult       $8, $6, $7;
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    sll        $6, $6, 4;
    and        $5, $5, $2;
    lw         $3, 0x40($4);
    lui        $2, (0x20000000 >> 16);
    sll        $7, $7, 4;
    or         $5, $5, $2;
    sw         $7, 0xF4($3);
    sw         $5, 0xEC($3);
    sw         $8, 0xF8($3);
    sw         $6, 0xF0($3);
    jal        MpegGetPictureImpl_1108a8;
    sw        $0, 0xC4($3);
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
