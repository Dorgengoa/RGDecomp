#include "types.h"

asm void IeeeSqrtf_125988(void)
{
    .set noreorder;
    mfc1       $3, $f12;
    daddu      $5, $3, $0;
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $3, (0x7FFFFF >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    ori        $3, $3, (0x7FFFFF & 0xFFFF);
    and        $2, $5, $2;
    sltu       $2, $3, $2;
    beqz       $2, L001259C8;
    mov.s     $f0, $f12;
    bgez       $5, L001259D0;
    sra       $7, $5, 23;
    sub.s      $f0, $f12, $f12;
    nop;
    nop;
    div.s      $f0, $f0, $f0;
  L001259C8:
    jr         $31;
    nop;
  L001259D0:
    addiu      $7, $7, -0x7F;
    lui        $2, (0x800000 >> 16);
    and        $3, $5, $3;
    andi       $4, $7, 0x1;
    or         $5, $3, $2;
    daddu      $8, $0, $0;
    sllv       $5, $5, $4;
    lui        $4, (0x1000000 >> 16);
    sra        $7, $7, 1;
    sll        $5, $5, 1;
    daddu      $6, $0, $0;
    nop;
  L00125A00:
    addu       $3, $8, $4;
    slt        $2, $5, $3;
    bnel       $2, $0, L00125A20;
    srl       $4, $4, 1;
    subu       $5, $5, $3;
    addu       $8, $3, $4;
    addu       $6, $6, $4;
    srl        $4, $4, 1;
  L00125A20:
    bnez       $4, L00125A00;
    sll       $5, $5, 1;
    beqz       $5, L00125A34;
    andi      $2, $6, 0x1;
    addu       $6, $6, $2;
  L00125A34:
    sra        $2, $6, 1;
    sll        $3, $7, 23;
    lui        $5, (0x3F000000 >> 16);
    addu       $5, $5, $2;
    addu       $5, $5, $3;
    mtc1       $5, $f0;
    jr         $31;
    nop;
}
