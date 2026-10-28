#include "types.h"

asm void KCopyBody_120db0(void)
{
    .set noreorder;
    srl        $6, $6, 2;
    beqz       $6, L00120DE0;
    daddu     $7, $0, $0;
    nop;
  L00120DC0:
    lw         $3, 0x0($5);
    addiu      $7, $7, 0x1;
    addiu      $5, $5, 0x4;
    sltu       $2, $7, $6;
    sw         $3, 0x0($4);
    addiu      $4, $4, 0x4;
    bnez       $2, L00120DC0;
    nop;
  L00120DE0:
    jr         $31;
    daddu     $2, $0, $0;
}
