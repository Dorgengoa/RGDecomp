#include "types.h"

extern void sceSifCallRpc(void);
extern void scePadSetReqState(void);

asm void scePadSetActAlign(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    lui        $3, 0x49;
    sd         $18, 0x30($29);
    addiu      $2, $0, 0x8;
    sd         $17, 0x20($29);
    daddu      $18, $4, $0;
    sd         $16, 0x10($29);
    daddu      $17, $5, $0;
    addiu      $16, $3, -0x10C0;
    sd         $31, 0x40($29);
    sw         $2, -0x10C0($3);
    addiu      $7, $16, 0xC;
    sw         $18, 0x4($16);
    daddu      $5, $0, $0;
    sw         $17, 0x8($16);
    nop;
  L0012BF98:
    addu       $2, $6, $5;
    addu       $4, $7, $5;
    lbu        $3, 0x0($2);
    addiu      $5, $5, 0x1;
    slti       $2, $5, 0x6;
    sb         $3, 0x0($4);
    bnez       $2, L0012BF98;
    nop;
    lui        $4, 0x49;
    sw         $0, 0x0($29);
    addiu      $4, $4, -0x1300;
    addiu      $5, $0, 0x1;
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012BFF4;
    lw        $3, 0x14($16);
    b          L0012C018;
    daddu     $2, $0, $0;
  L0012BFF4:
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0012C018;
    daddu     $2, $3, $0;
    daddu      $4, $18, $0;
    daddu      $5, $17, $0;
    jal        scePadSetReqState;
    addiu     $6, $0, 0x2;
    lw         $3, 0x14($16);
    daddu      $2, $3, $0;
  L0012C018:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
