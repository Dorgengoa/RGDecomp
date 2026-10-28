#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void iGetTimerSystemTime_1217b8(void);

asm void SetTimerCount_121cf8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $18, 0x20($29);
    sd         $16, 0x0($29);
    srl        $2, $17, 10;
    sd         $19, 0x30($29);
    daddu      $18, $5, $0;
    sd         $31, 0x40($29);
    jal        DisableIntr_120660;
    sll       $16, $2, 6;
    bltz       $17, L00121D4C;
    daddu     $19, $2, $0;
    lw         $3, 0x8($16);
    andi       $2, $17, 0x3FF;
    bne        $2, $3, L00121D4C;
    lui       $2, 0x44;
    addiu      $2, $2, 0x78A8;
    lw         $3, 0x1C($2);
    bnel       $3, $17, L00121D64;
    lw        $2, 0xC($16);
  L00121D4C:
    beqz       $19, L00121DA8;
    addiu     $2, $0, -0x1;
    jal        EnableIntr_1206b0;
    nop;
    b          L00121DA8;
    addiu     $2, $0, -0x1;
  L00121D64:
    andi       $2, $2, 0x1;
    beqz       $2, L00121D90;
    ld        $17, 0x18($16);
    jal        iGetTimerSystemTime_1217b8;
    nop;
    ld         $3, 0x10($16);
    sd         $18, 0x18($16);
    dsubu      $3, $2, $3;
    sd         $2, 0x10($16);
    b          L00121D94;
    daddu     $17, $17, $3;
  L00121D90:
    sd         $18, 0x18($16);
  L00121D94:
    beqz       $19, L00121DA8;
    daddu     $2, $17, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $17, $0;
  L00121DA8:
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
