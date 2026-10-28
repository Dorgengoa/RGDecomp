#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceSifGetNextRequest(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    daddu     $16, $4, $0;
    lw         $17, 0xC($16);
    bnel       $17, $0, L0011A9E4;
    lw        $3, 0x3C($17);
    b          L0011A9F0;
    sw        $0, 0x4($16);
  L0011A9E4:
    addiu      $2, $0, 0x1;
    sw         $2, 0x4($16);
    sw         $3, 0xC($16);
  L0011A9F0:
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $17, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
