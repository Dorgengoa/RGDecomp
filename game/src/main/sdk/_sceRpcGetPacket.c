#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void _sceRpcGetPacket(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    daddu     $17, $4, $0;
    lw         $4, 0x8($17);
    daddu      $3, $0, $0;
    blez       $4, L00119DB0;
    lw        $16, 0x4($17);
    addiu      $5, $0, 0x1;
    nop;
  L00119D58:
    lw         $2, 0x10($16);
    andi       $2, $2, 0x1;
    bnel       $2, $0, L00119DA4;
    addiu     $3, $3, 0x1;
    sll        $2, $3, 16;
    ori        $2, $2, 0x5;
    sw         $2, 0x10($16);
    lw         $2, 0x0($17);
    addiu      $3, $2, 0x1;
    bne        $3, $5, L00119D90;
    sw        $3, 0x0($17);
    addiu      $2, $2, 0x2;
    addiu      $3, $0, 0x1;
    sw         $2, 0x0($17);
  L00119D90:
    sw         $16, 0x14($16);
    jal        EnableIntr_1206b0;
    sw        $3, 0x18($16);
    b          L00119DBC;
    daddu     $2, $16, $0;
  L00119DA4:
    slt        $2, $3, $4;
    bnez       $2, L00119D58;
    addiu     $16, $16, 0x40;
  L00119DB0:
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $0, $0;
  L00119DBC:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
