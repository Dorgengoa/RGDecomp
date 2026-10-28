#include "types.h"

extern void sceGsPutDispEnv(void);
extern void sceGsPutDrawEnv(void);

asm void sceGsSwapDBuff(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    andi       $16, $5, 0x1;
    addiu      $4, $0, 0x28;
    mult       $2, $16, $4;
    sd         $31, 0x20($29);
    jal        sceGsPutDispEnv;
    addu      $4, $2, $17;
    beqz       $16, L00108F78;
    nop;
    jal        sceGsPutDrawEnv;
    addiu     $4, $17, 0x140;
    b          L00108F84;
    ld        $31, 0x20($29);
  L00108F78:
    jal        sceGsPutDrawEnv;
    addiu     $4, $17, 0x50;
    ld         $31, 0x20($29);
  L00108F84:
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

