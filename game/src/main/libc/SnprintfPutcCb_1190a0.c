#include "types.h"

asm void SnprintfPutcCb_1190a0(void)
{
    .set noreorder;
    lw         $3, 0x0($5);
    bnez       $3, L001190B4;
    daddu     $7, $4, $0;
    jr         $31;
    addiu     $2, $0, 0x1;
  L001190B4:
    slti       $2, $6, 0x100;
    beql       $2, $0, L001190EC;
    lw        $3, 0x0($7);
    xori       $2, $3, 0x1;
    lw         $4, 0x0($7);
    movz       $6, $0, $2;
    sb         $6, 0x0($4);
    addiu      $2, $0, 0x1;
    addiu      $4, $4, 0x1;
    lw         $3, 0x0($5);
    sw         $4, 0x0($7);
    addiu      $3, $3, -0x1;
    jr         $31;
    sw        $3, 0x0($5);
  L001190EC:
    daddu      $2, $0, $0;
    jr         $31;
    sb        $0, 0x0($3);
}
