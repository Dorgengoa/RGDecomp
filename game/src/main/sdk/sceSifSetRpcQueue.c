#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceSifSetRpcQueue(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    daddu     $16, $5, $0;
    lui        $3, 0x49;
    sw         $16, 0x0($17);
    addiu      $3, $3, -0x7CC0;
    sw         $0, 0x4($17);
    lw         $2, 0x28($3);
    sw         $0, 0x8($17);
    sw         $0, 0xC($17);
    sw         $0, 0x10($17);
    bnez       $2, L0011A774;
    sw        $0, 0x14($17);
    b          L0011A7A8;
    sw        $17, 0x28($3);
  L0011A774:
    daddu      $4, $2, $0;
    lw         $3, 0x14($4);
    beql       $3, $0, L0011A7A8;
    sw        $17, 0x14($4);
    nop;
  L0011A788:
    daddu      $4, $3, $0;
    lw         $2, 0x14($4);
    daddu      $3, $2, $0;
    nop;
    nop;
    bnez       $2, L0011A788;
    nop;
    sw         $17, 0x14($4);
  L0011A7A8:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x30;
}
