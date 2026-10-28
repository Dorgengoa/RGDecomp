#include "types.h"

asm void sceGifPkTerminate_10a420(void)
{
    .set noreorder;
    lw         $5, 0x0($4);
    andi       $2, $5, 0xC;
    beqz       $2, L0010A44C;
    lw        $6, 0x8($4);
  L0010A430:
    sw         $0, 0x0($5);
    addiu      $5, $5, 0x4;
    andi       $2, $5, 0xC;
    nop;
    nop;
    bnez       $2, L0010A430;
    nop;
  L0010A44C:
    beqz       $6, L0010A468;
    subu      $2, $5, $6;
    lw         $3, 0x0($6);
    sra        $2, $2, 4;
    addiu      $2, $2, -0x1;
    addu       $3, $3, $2;
    sw         $3, 0x0($6);
  L0010A468:
    sw         $0, 0x8($4);
    daddu      $2, $5, $0;
    jr         $31;
    sw        $5, 0x0($4);
}

