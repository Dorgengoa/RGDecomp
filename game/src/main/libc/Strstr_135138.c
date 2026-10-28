#include "types.h"

asm void Strstr_135138(void)
{
    .set noreorder;
    lb         $2, 0x0($4);
    bnez       $2, L00135158;
    lb        $3, 0x0($5);
    daddu      $2, $0, $0;
    jr         $31;
    movz      $2, $4, $3;
  L00135150:
    jr         $31;
    daddu     $2, $4, $0;
  L00135158:
    nop;
    nop;
    nop;
    beqz       $3, L00135150;
    daddu     $7, $0, $0;
    lb         $2, 0x0($4);
    bnel       $3, $2, L001351A8;
    addiu     $4, $4, 0x1;
    addiu      $7, $7, 0x1;
    nop;
  L00135180:
    addu       $2, $5, $7;
    lb         $3, 0x0($2);
    beqz       $3, L00135150;
    addu      $6, $4, $7;
    lb         $2, 0x0($6);
    nop;
    nop;
    beql       $3, $2, L00135180;
    addiu     $7, $7, 0x1;
    addiu      $4, $4, 0x1;
  L001351A8:
    lb         $2, 0x0($4);
    bnel       $2, $0, L00135158;
    lb        $3, 0x0($5);
    jr         $31;
    daddu     $2, $0, $0;
}

