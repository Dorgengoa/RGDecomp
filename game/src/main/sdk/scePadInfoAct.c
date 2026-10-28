#include "types.h"

extern void scePadGetDmaStr(void);

asm void scePadInfoAct(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $8, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0xB0;
    lui        $2, 0x49;
    sd         $17, 0x90($29);
    sd         $16, 0x80($29);
    addiu      $2, $2, -0x12B0;
    sd         $31, 0xA0($29);
    daddu      $17, $6, $0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    beqz       $3, L0012BB70;
    daddu     $16, $7, $0;
    daddu      $4, $8, $0;
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lbu        $4, 0x72($29);
    addiu      $2, $0, 0x1;
    bne        $4, $2, L0012BB74;
    daddu     $2, $0, $0;
    lbu        $2, 0x64($29);
    sltiu      $2, $2, 0x2;
    bnez       $2, L0012BB74;
    daddu     $2, $0, $0;
    lbu        $3, 0x6A($29);
    slt        $2, $17, $3;
    beqz       $2, L0012BB70;
    addiu     $2, $0, -0x1;
    bne        $17, $2, L0012BB00;
    addiu     $2, $0, 0x2;
    b          L0012BB74;
    daddu     $2, $3, $0;
  L0012BB00:
    beq        $16, $2, L0012BB4C;
    sll       $2, $17, 2;
    slti       $2, $16, 0x3;
    beql       $2, $0, L0012BB24;
    addiu     $2, $0, 0x3;
    beq        $16, $4, L0012BB40;
    sll       $2, $17, 2;
    b          L0012BB74;
    daddu     $2, $0, $0;
  L0012BB24:
    beq        $16, $2, L0012BB58;
    sll       $2, $17, 2;
    addiu      $2, $0, 0x4;
    beq        $16, $2, L0012BB64;
    sll       $2, $17, 2;
    b          L0012BB74;
    daddu     $2, $0, $0;
  L0012BB40:
    addu       $3, $29, $2;
    b          L0012BB74;
    lbu       $2, 0x30($3);
  L0012BB4C:
    addu       $3, $29, $2;
    b          L0012BB74;
    lbu       $2, 0x31($3);
  L0012BB58:
    addu       $3, $29, $2;
    b          L0012BB74;
    lbu       $2, 0x32($3);
  L0012BB64:
    addu       $3, $29, $2;
    b          L0012BB74;
    lbu       $2, 0x33($3);
  L0012BB70:
    daddu      $2, $0, $0;
  L0012BB74:
    ld         $31, 0xA0($29);
    ld         $17, 0x90($29);
    ld         $16, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
}
