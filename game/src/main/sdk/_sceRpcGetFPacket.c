#include "types.h"

asm void _sceRpcGetFPacket(void)
{
    .set noreorder;
    lw         $5, 0x24($4);
    lw         $3, 0x18($4);
    div $5, $3;
    beql       $3, $0, L00119E04;
        .word 0x000001CD;
  L00119E04:
    lw         $5, 0x14($4);
    mfhi       $2;
    addiu      $3, $2, 0x1;
    sll        $2, $2, 6;
    sw         $3, 0x24($4);
    jr         $31;
    addu      $2, $5, $2;
}

