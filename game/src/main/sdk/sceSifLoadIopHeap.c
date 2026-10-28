#include "types.h"

extern void sceSifCallRpc(void);

asm void sceSifLoadIopHeap(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $29, $29, -0x30;
    lw         $3, 0x62B8($2);
    daddu      $6, $4, $0;
    sd         $31, 0x20($29);
    bgez       $3, L0011EA84;
    sd        $16, 0x10($29);
    b          L0011EB40;
    daddu     $2, $0, $0;
  L0011EA84:
    lbu        $2, 0x0($6);
    lui        $7, 0x49;
    addiu      $3, $7, -0x6380;
    sb         $2, 0x4($3);
    sll        $2, $2, 24;
    beqz       $2, L0011EAE0;
    daddu     $8, $0, $0;
    lui        $9, 0x49;
    lui        $16, 0x49;
    addiu      $8, $8, 0x1;
    nop;
  L0011EAB0:
    slti       $2, $8, 0xFC;
    beqz       $2, L0011EAE8;
    addu      $2, $6, $8;
    addiu      $3, $7, -0x6380;
    lbu        $4, 0x0($2);
    addu       $3, $3, $8;
    sb         $4, 0x4($3);
    sll        $4, $4, 24;
    bnel       $4, $0, L0011EAB0;
    addiu     $8, $8, 0x1;
    b          L0011EAEC;
    addiu     $2, $0, 0xFC;
  L0011EAE0:
    lui        $9, 0x49;
    lui        $16, 0x49;
  L0011EAE8:
    addiu      $2, $0, 0xFC;
  L0011EAEC:
    bnel       $8, $2, L0011EB04;
    sw        $5, -0x6380($7);
    addiu      $2, $7, -0x6380;
    addiu      $8, $0, 0xFB;
    sb         $0, 0xFF($2);
    sw         $5, -0x6380($7);
  L0011EB04:
    addiu      $2, $7, -0x6380;
    addiu      $4, $9, -0x6440;
    sb         $0, 0xFF($2);
    daddu      $7, $2, $0;
    addiu      $8, $8, 0x5;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x3;
    daddu      $6, $0, $0;
    addiu      $9, $16, -0x6400;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0011EB40;
    lw        $2, -0x6400($16);
    addiu      $2, $0, -0x1;
  L0011EB40:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
