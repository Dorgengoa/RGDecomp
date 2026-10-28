#include "types.h"

extern void sceSifCallRpc(void);
extern void DelayThread_117618(void);

asm void SifCallRpcRetry_11ad90(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $30, 0xA0($29);
    sd         $23, 0x90($29);
    daddu      $30, $6, $0;
    sd         $22, 0x80($29);
    daddu      $23, $7, $0;
    sd         $21, 0x70($29);
    daddu      $22, $8, $0;
    sd         $20, 0x60($29);
    daddu      $21, $9, $0;
    sd         $19, 0x50($29);
    daddu      $20, $10, $0;
    sd         $18, 0x40($29);
    daddu      $19, $11, $0;
    sd         $17, 0x30($29);
    daddu      $18, $0, $0;
    sd         $31, 0xB0($29);
    addiu      $17, $0, 0x1;
    sd         $16, 0x20($29);
    sw         $4, 0x10($29);
    sw         $5, 0x14($29);
    lw         $2, 0xC0($29);
  L0011ADE8:
    daddu      $6, $30, $0;
    lw         $4, 0x10($29);
    daddu      $7, $23, $0;
    lw         $5, 0x14($29);
    daddu      $8, $22, $0;
    sw         $2, 0x0($29);
    daddu      $9, $21, $0;
    daddu      $10, $20, $0;
    jal        sceSifCallRpc;
    daddu     $11, $19, $0;
    srl        $16, $2, 31;
    beqz       $16, L0011AE48;
    lw        $2, 0xC8($29);
    bnez       $2, L0011AE48;
    addiu     $2, $0, 0x3E8;
    jal        DelayThread_117618;
    mult      $4, $17, $2;
    slti       $3, $17, 0x7F;
    bnel       $3, $0, L0011AE38;
    sll       $17, $17, 1;
  L0011AE38:
    addiu      $18, $18, 0x1;
    slti       $2, $18, 0x65;
    bnez       $2, L0011ADE8;
    lw        $2, 0xC0($29);
  L0011AE48:
    daddu      $2, $16, $0;
    ld         $31, 0xB0($29);
    ld         $30, 0xA0($29);
    ld         $23, 0x90($29);
    ld         $22, 0x80($29);
    ld         $21, 0x70($29);
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
