#include "types.h"

extern void sceSifCallRpc(void);
extern void scePadSetReqState(void);

asm void scePadSetVrefParam(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    lui        $2, 0x49;
    sd         $18, 0x30($29);
    addiu      $3, $0, 0xB;
    sd         $16, 0x10($29);
    daddu      $18, $4, $0;
    addiu      $16, $2, -0x10C0;
    sd         $17, 0x20($29);
    sd         $31, 0x40($29);
    daddu      $17, $5, $0;
    sw         $18, 0x4($16);
    lui        $4, 0x49;
    sw         $3, -0x10C0($2);
    addiu      $4, $4, -0x1300;
    sw         $17, 0x8($16);
    addiu      $8, $0, 0x80;
    ldl        $2, 0x7($6);
    ldr        $2, 0x0($6);
    lwl        $3, 0xB($6);
    lwr        $3, 0x8($6);
    sdl        $2, 0x13($16);
    sdr        $2, 0xC($16);
    swl        $3, 0x17($16);
    swr        $3, 0x14($16);
    daddu      $9, $16, $0;
    addiu      $5, $0, 0x1;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012C330;
    lw        $3, 0x1C($16);
    b          L0012C354;
    daddu     $2, $0, $0;
  L0012C330:
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0012C354;
    daddu     $2, $3, $0;
    daddu      $4, $18, $0;
    daddu      $5, $17, $0;
    jal        scePadSetReqState;
    addiu     $6, $0, 0x2;
    lw         $3, 0x1C($16);
    daddu      $2, $3, $0;
  L0012C354:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
