#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceSifRegisterRpc(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $22, 0x60($29);
    sd         $21, 0x50($29);
    daddu      $22, $10, $0;
    sd         $20, 0x40($29);
    daddu      $21, $4, $0;
    sd         $19, 0x30($29);
    daddu      $20, $9, $0;
    sd         $18, 0x20($29);
    daddu      $19, $8, $0;
    sd         $17, 0x10($29);
    daddu      $18, $7, $0;
    sd         $16, 0x0($29);
    daddu      $17, $6, $0;
    sd         $31, 0x70($29);
    jal        DisableIntr_120660;
    daddu     $16, $5, $0;
    sw         $0, 0x3C($21);
    sw         $0, 0x38($21);
    sw         $16, 0x0($21);
    lw         $2, 0x8($22);
    sw         $17, 0x4($21);
    sw         $18, 0x8($21);
    sw         $19, 0x10($21);
    sw         $20, 0x14($21);
    bnez       $2, L0011A834;
    sw        $22, 0x40($21);
    b          L0011A868;
    sw        $21, 0x8($22);
  L0011A834:
    daddu      $4, $2, $0;
    lw         $3, 0x38($4);
    beql       $3, $0, L0011A868;
    sw        $21, 0x38($4);
    nop;
  L0011A848:
    daddu      $4, $3, $0;
    lw         $2, 0x38($4);
    daddu      $3, $2, $0;
    nop;
    nop;
    bnez       $2, L0011A848;
    nop;
    sw         $21, 0x38($4);
  L0011A868:
    ld         $31, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x80;
}
