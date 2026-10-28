#include "types.h"

extern void DisableIntr_120660(void);
extern void RemoveIntcHandler(void);
extern void DisableIntc_117080(void);
extern void Timer2SetMode_120f50(void);
extern void Timer2SetCount_120f40(void);
extern void EnableIntr_1206b0(void);

asm void EndTimer_1210c8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $18, 0x20($29);
    sd         $16, 0x0($29);
    lui        $18, 0x44;
    sd         $31, 0x30($29);
    addiu      $16, $18, 0x78A8;
    sd         $17, 0x10($29);
    lw         $2, 0x8($16);
    bgez       $2, L001210FC;
    nop;
    lui        $2, (0x80008001 >> 16);
    b          L00121168;
    ori       $2, $2, (0x80008001 & 0xFFFF);
  L001210FC:
    lw         $2, 0x10($16);
    beqz       $2, L00121114;
    nop;
    lui        $2, (0x80000010 >> 16);
    b          L00121168;
    ori       $2, $2, (0x80000010 & 0xFFFF);
  L00121114:
    jal        DisableIntr_120660;
    nop;
    lw         $5, 0x8($16);
    daddu      $17, $2, $0;
    jal        RemoveIntcHandler;
    addiu     $4, $0, 0xB;
    bnez       $2, L00121150;
    addiu     $2, $0, -0x1;
    jal        DisableIntc_117080;
    addiu     $4, $0, 0xB;
    jal        Timer2SetMode_120f50;
    addiu     $4, $0, 0xC00;
    jal        Timer2SetCount_120f40;
    daddu     $4, $0, $0;
    addiu      $2, $0, -0x1;
  L00121150:
    sd         $0, 0x78A8($18);
    beqz       $17, L00121164;
    sw        $2, 0x8($16);
    jal        EnableIntr_1206b0;
    nop;
  L00121164:
    daddu      $2, $0, $0;
  L00121168:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
