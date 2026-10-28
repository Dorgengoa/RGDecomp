#include "types.h"

extern void DisableIntr_120660(void);
extern void sceSifAddCmdHandler(void);
extern void EnableIntr_1206b0(void);

asm void PowerOffCB_129768(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    addiu      $18, $0, 0x1;
    lui        $17, 0x44;
    sd         $16, 0x0($29);
    sd         $31, 0x30($29);
    jal        DisableIntr_120660;
    sw        $18, 0x7964($17);
    lui        $5, 0x13;
    lui        $4, (0x80000012 >> 16);
    daddu      $16, $2, $0;
    addiu      $5, $5, -0x68F0;
    ori        $4, $4, (0x80000012 & 0xFFFF);
    jal        sceSifAddCmdHandler;
    daddu     $6, $0, $0;
    beqz       $16, L001297BC;
    lui       $2, 0x44;
    jal        EnableIntr_1206b0;
    nop;
    lui        $2, 0x44;
  L001297BC:
    sw         $0, 0x7964($17);
    sw         $18, 0x7988($2);
    ld         $31, 0x30($29);
    addiu      $2, $0, 0x1;
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
