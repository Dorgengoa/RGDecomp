#include "types.h"

asm void MbtowcR_1317f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $2, $0, $0;
    daddu      $3, $29, $0;
    beqz       $6, L00131824;
    movn      $3, $5, $5;
    beqz       $7, L00131824;
    addiu     $2, $0, -0x1;
    lbu        $2, 0x0($6);
    sw         $2, 0x0($3);
    lbu        $2, 0x0($6);
    sltu       $2, $0, $2;
  L00131824:
    jr         $31;
    addiu     $29, $29, 0x10;
}
