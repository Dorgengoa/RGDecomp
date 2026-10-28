#include "types.h"

extern void iGetTimerSystemTime_1217b8(void);

asm void iGetTimerCount_121e60(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    srl        $2, $4, 10;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    sll        $17, $2, 6;
    bltz       $4, L00121E8C;
    sd        $16, 0x0($29);
    lw         $3, 0x8($17);
    andi       $2, $4, 0x3FF;
    beql       $2, $3, L00121E94;
    lw        $2, 0xC($17);
  L00121E8C:
    b          L00121EB8;
    addiu     $2, $0, -0x1;
  L00121E94:
    andi       $2, $2, 0x1;
    beqz       $2, L00121EB4;
    ld        $16, 0x18($17);
    jal        iGetTimerSystemTime_1217b8;
    nop;
    ld         $3, 0x10($17);
    dsubu      $2, $2, $3;
    daddu      $16, $16, $2;
  L00121EB4:
    daddu      $2, $16, $0;
  L00121EB8:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
