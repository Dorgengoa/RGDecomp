#include "types.h"

extern void sceSifCallRpc(void);

asm void scePadPortClose(void)
{
    .set noreorder;
    daddu      $7, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $7, $3;
    mult       $4, $5, $4;
    lui        $2, 0x49;
    addiu      $29, $29, -0x40;
    addiu      $2, $2, -0x12B0;
    sd         $17, 0x20($29);
    addiu      $2, $2, 0x10;
    sd         $31, 0x30($29);
    addu       $4, $4, $3;
    sd         $16, 0x10($29);
    addu       $17, $4, $2;
    lw         $3, 0x0($17);
    beqz       $3, L0012B63C;
    daddu     $2, $0, $0;
    lui        $2, 0x49;
    addiu      $3, $0, 0xE;
    addiu      $16, $2, -0x10C0;
    sw         $3, -0x10C0($2);
    addiu      $6, $0, 0x1;
    sw         $7, 0x4($16);
    sw         $5, 0x8($16);
    lui        $4, 0x49;
    sw         $6, 0x10($16);
    addiu      $4, $4, -0x1300;
    addiu      $5, $0, 0x1;
    daddu      $6, $0, $0;
    sw         $0, 0x0($29);
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012B638;
    sw        $0, 0x0($17);
    b          L0012B63C;
    daddu     $2, $0, $0;
  L0012B638:
    lw         $2, 0xC($16);
  L0012B63C:
    ld         $31, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
