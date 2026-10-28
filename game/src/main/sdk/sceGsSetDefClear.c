#include "types.h"

asm void sceGsSetDefClear(void)
{
    .set noreorder;
    sll        $7, $7, 16;
    sll        $9, $9, 16;
    sra        $7, $7, 16;
    sra        $9, $9, 16;
    addu       $9, $7, $9;
    sll        $6, $6, 16;
    sll        $8, $8, 16;
    lbu        $12, 0x0($29);
    sra        $6, $6, 16;
    sra        $8, $8, 16;
    sll        $9, $9, 4;
    sll        $7, $7, 4;
    lwu        $3, 0x10($29);
    addu       $8, $6, $8;
    andi       $11, $11, 0xFF;
    lbu        $13, 0x8($29);
    dsll       $11, $11, 8;
    ori        $2, $0, 0xFE00;
    dsll32     $2, $2, 14;
    sll        $8, $8, 4;
    sll        $6, $6, 4;
    andi       $10, $10, 0xFF;
    dsll       $12, $12, 16;
    dsll       $7, $7, 16;
    dsll       $9, $9, 16;
    dsll32     $3, $3, 0;
    or         $10, $10, $2;
    or         $12, $12, $11;
    or         $7, $6, $7;
    or         $9, $8, $9;
    sll        $5, $5, 16;
    daddu      $6, $4, $0;
    or         $9, $9, $3;
    or         $7, $7, $3;
    or         $10, $10, $12;
    dsll       $13, $13, 24;
    sra        $8, $5, 16;
    addiu      $4, $0, 0x47;
    addiu      $5, $0, 0x5;
    or         $10, $10, $13;
    lui        $11, (0x30000 >> 16);
    addiu      $2, $0, 0x6;
    addiu      $3, $0, 0x1;
    sd         $2, 0x10($6);
    sd         $3, 0x28($6);
    sd         $10, 0x20($6);
    sd         $7, 0x30($6);
    sd         $5, 0x48($6);
    sd         $9, 0x40($6);
    sd         $4, 0x58($6);
    sd         $4, 0x8($6);
    sd         $11, 0x0($6);
    sd         $0, 0x18($6);
    beqz       $8, L00108BA4;
    sd        $5, 0x38($6);
    andi       $2, $8, 0x3;
    lui        $3, (0x10000 >> 16);
    dsll       $2, $2, 17;
    or         $2, $2, $3;
    b          L00108BA8;
    sd        $2, 0x50($6);
  L00108BA4:
    sd         $11, 0x50($6);
  L00108BA8:
    sync;
    jr         $31;
    addiu     $2, $0, 0x6;
}

