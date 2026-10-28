#include "types.h"

extern void sceSifGetReg(void);
extern void sceResetttyinit_116a20(void);
extern void IopResetCallbacksInvokeMaybe_1227e8(void);

asm void sceSifSyncIop_11fc80(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        sceSifGetReg;
    addiu     $4, $0, 0x4;
    lui        $3, (0x40000 >> 16);
    and        $2, $2, $3;
    beqz       $2, L0011FCC4;
    daddu     $2, $0, $0;
    jal        sceResetttyinit_116a20;
    nop;
    addiu      $4, $0, 0x1;
    jal        IopResetCallbacksInvokeMaybe_1227e8;
    addiu     $5, $0, 0x1;
    daddu      $4, $0, $0;
    jal        IopResetCallbacksInvokeMaybe_1227e8;
    addiu     $5, $0, 0x1;
    addiu      $2, $0, 0x1;
  L0011FCC4:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
