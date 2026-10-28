#include "types.h"

extern void sceSifCallRpc(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void PadSetCmdCallbackMaybe_12c510(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $18, 0x30($29);
    sd         $20, 0x50($29);
    lui        $18, 0x45;
    sd         $17, 0x20($29);
    daddu      $20, $4, $0;
    sd         $31, 0x70($29);
    sd         $21, 0x60($29);
    sd         $19, 0x40($29);
    sd         $16, 0x10($29);
    bnez       $20, L0012C594;
    lw        $17, -0x6AF0($18);
    lui        $3, 0x49;
    addiu      $2, $0, 0x18;
    sw         $2, -0x10C0($3);
    addiu      $16, $3, -0x10C0;
    sw         $0, -0x6AF0($18);
    lui        $19, 0x49;
    sw         $0, 0x4($16);
    sw         $0, 0x0($29);
  L0012C560:
    addiu      $4, $19, -0x1300;
    addiu      $5, $0, 0x1;
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bltzl      $2, L0012C560;
    sw        $0, 0x0($29);
    b          L0012C610;
    daddu     $2, $17, $0;
  L0012C594:
    bnez       $17, L0012C5EC;
    lui       $21, 0x49;
    lui        $2, 0x49;
    addiu      $3, $0, 0x18;
    sw         $3, -0x10C0($2);
    addiu      $16, $2, -0x10C0;
    addiu      $3, $0, 0x1;
    lui        $19, 0x49;
    sw         $3, 0x4($16);
    sw         $0, 0x0($29);
    nop;
  L0012C5C0:
    addiu      $4, $19, -0x1300;
    addiu      $5, $0, 0x1;
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bltzl      $2, L0012C5C0;
    sw        $0, 0x0($29);
  L0012C5EC:
    jal        DisableIntr_120660;
    nop;
    sw         $28, -0x1040($21);
    addiu      $3, $0, 0x1;
    bne        $2, $3, L0012C60C;
    sw        $20, -0x6AF0($18);
    jal        EnableIntr_1206b0;
    nop;
  L0012C60C:
    daddu      $2, $17, $0;
  L0012C610:
    ld         $31, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
