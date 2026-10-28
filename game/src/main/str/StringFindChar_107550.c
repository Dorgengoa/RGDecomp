#include "types.h"

asm void StringFindChar_107550(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    andi       $2, $2, 0x1;
    bnel       $2, $0, L00107574;
    lw        $7, 0x8($4);
    lbu        $2, 0x0($4);
    addiu      $7, $4, 0x1;
    dsll32     $2, $2, 24;
    b          L00107578;
    dsrl32    $2, $2, 25;
  L00107574:
    lw         $2, 0x4($4);
  L00107578:
    sltu       $1, $6, $2;
    beqz       $1, L001075C0;
    nop;
    addu       $4, $7, $2;
    addu       $6, $7, $6;
    sltu       $1, $6, $4;
    beqz       $1, L001075C0;
    nop;
    dsll32     $3, $5, 24;
    dsra32     $3, $3, 24;
    lb         $2, 0x0($6);
  L001075A4:
    beql       $2, $3, L001075B4;
    addiu     $6, $6, 0x1;
    b          L001075C4;
    subu      $2, $6, $7;
  L001075B4:
    sltu       $2, $6, $4;
    bnel       $2, $0, L001075A4;
    lb        $2, 0x0($6);
  L001075C0:
    addiu      $2, $0, -0x1;
  L001075C4:
    jr         $31;
    nop;
}

