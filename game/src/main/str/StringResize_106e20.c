#include "types.h"

extern void StringReplaceFill_1075d0(void);

asm void StringResize_106e20(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    lw         $2, 0x0($4);
    andi       $2, $2, 0x1;
    beqz       $2, L00106E40;
    daddu     $8, $6, $0;
    b          L00106E4C;
    lw        $2, 0x4($4);
  L00106E40:
    lbu        $2, 0x0($4);
    dsll32     $2, $2, 24;
    dsrl32     $2, $2, 25;
  L00106E4C:
    sltu       $1, $2, $5;
    beql       $1, $0, L00106E70;
    subu      $6, $2, $5;
    subu       $7, $5, $2;
    daddu      $6, $0, $0;
    jal        StringReplaceFill_1075d0;
    daddu     $5, $2, $0;
    b          L00106E80;
    ld        $31, 0x0($29);
  L00106E70:
    daddu      $7, $0, $0;
    jal        StringReplaceFill_1075d0;
    daddu     $8, $0, $0;
    ld         $31, 0x0($29);
  L00106E80:
    jr         $31;
    addiu     $29, $29, 0x10;
}

