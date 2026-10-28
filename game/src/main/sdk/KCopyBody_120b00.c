#include "types.h"

asm void KCopyBody_120b00(void)
{
    .set noreorder;
    beqz       $6, L00120B28;
    daddu     $7, $0, $0;
  L00120B08:
    lbu        $3, 0x0($5);
    addiu      $7, $7, 0x1;
    addiu      $5, $5, 0x1;
    sltu       $2, $7, $6;
    sb         $3, 0x0($4);
    addiu      $4, $4, 0x1;
    bnez       $2, L00120B08;
    nop;
  L00120B28:
    jr         $31;
    daddu     $2, $0, $0;
}
