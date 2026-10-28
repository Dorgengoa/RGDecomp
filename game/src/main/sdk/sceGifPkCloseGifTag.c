#include "types.h"

asm void sceGifPkCloseGifTag(void)
{
    .set noreorder;
    daddu      $9, $4, $0;
    addiu      $5, $0, 0x2;
    lw         $8, 0xC($9);
    lw         $10, 0x0($9);
    ld         $7, 0x0($8);
    subu       $2, $10, $8;
    sra        $2, $2, 3;
    dsrl32     $3, $7, 26;
    addiu      $6, $2, -0x2;
    andi       $3, $3, 0x3;
    srl        $4, $6, 1;
    xori       $2, $3, 0x1;
    beq        $3, $5, L0010A690;
    movn      $6, $4, $2;
    dsrl32     $2, $7, 28;
    addiu      $4, $0, 0x10;
    movz       $2, $4, $2;
    addu       $3, $6, $2;
    beql       $2, $0, L0010A680;
        .word 0x000001CD;
  L0010A680:
    addiu      $3, $3, -0x1;
    divu $3, $2;
    mflo       $3;
    daddu      $6, $3, $0;
  L0010A690:
    dsll32     $2, $6, 0;
    daddu      $5, $10, $0;
    dsrl32     $2, $2, 0;
    sw         $0, 0xC($9);
    daddu      $2, $7, $2;
    andi       $3, $5, 0xC;
    beqz       $3, L0010A6CC;
    sd        $2, 0x0($8);
  L0010A6B0:
    sw         $0, 0x0($5);
    addiu      $5, $5, 0x4;
    andi       $2, $5, 0xC;
    nop;
    nop;
    bnez       $2, L0010A6B0;
    nop;
  L0010A6CC:
    jr         $31;
    sw        $5, 0x0($9);
}

