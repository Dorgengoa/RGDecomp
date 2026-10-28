#include "types.h"

extern void StringFindChar_107550(void);

asm void DecimalRoundDirectionMaybe_106ab0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    lw         $2, 0x0($4);
    andi       $2, $2, 0x1;
    sltu       $2, $0, $2;
    xori       $2, $2, 0x1;
    andi       $3, $2, 0xFF;
    beql       $3, $0, L00106AE0;
    lw        $2, 0x4($4);
    lbu        $2, 0x0($4);
    dsll32     $2, $2, 24;
    dsrl32     $2, $2, 25;
  L00106AE0:
    sltu       $2, $5, $2;
    bnez       $2, L00106AF4;
    nop;
    b          L00106B3C;
    addiu     $2, $0, -0x1;
  L00106AF4:
    beql       $3, $0, L00106B00;
    lw        $2, 0x8($4);
    addiu      $2, $4, 0x1;
  L00106B00:
    addu       $2, $2, $5;
    lb         $2, 0x0($2);
    slti       $1, $2, 0x6;
    bnel       $1, $0, L00106B1C;
    slti      $1, $2, 0x5;
    b          L00106B3C;
    addiu     $2, $0, 0x1;
  L00106B1C:
    beql       $1, $0, L00106B2C;
    addiu     $6, $5, 0x1;
    b          L00106B3C;
    addiu     $2, $0, -0x1;
  L00106B2C:
    jal        StringFindChar_107550;
    daddu     $5, $0, $0;
    not        $2, $2;
    sltu       $2, $0, $2;
  L00106B3C:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

