#include "types.h"

asm void UModDi3_13a430(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    dsra32     $9, $5, 0;
    dsra32     $10, $4, 0;
    dsll32     $7, $5, 0;
    dsra32     $7, $7, 0;
    dsll32     $13, $4, 0;
    dsra32     $13, $13, 0;
    bnez       $9, L0013A710;
    daddu     $24, $29, $0;
    sltu       $2, $10, $7;
    beqz       $2, L0013A4D8;
    ori       $2, $0, 0xFFFF;
    sltu       $2, $2, $7;
    bnez       $2, L0013A480;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $7, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013A494;
    movn      $4, $0, $2;
    nop;
  L0013A480:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $7;
    movn       $4, $3, $2;
  L0013A494:
    srlv       $3, $7, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x76C8($2);
    addu       $2, $2, $4;
    subu       $12, $5, $2;
    beqz       $12, L0013A4CC;
    subu      $2, $5, $12;
    sllv       $3, $10, $12;
    srlv       $2, $13, $2;
    sllv       $13, $13, $12;
    or         $10, $3, $2;
    sllv       $7, $7, $12;
  L0013A4CC:
    srl        $6, $7, 16;
    b          L0013A638;
    andi      $9, $7, 0xFFFF;
  L0013A4D8:
    bnez       $7, L0013A500;
    sltu      $2, $2, $7;
    addiu      $2, $0, 0x1;
    beql       $7, $0, L0013A4EC;
        .word 0x000001CD;
  L0013A4EC:
    divu $2, $9;
    mflo       $2;
    daddu      $7, $2, $0;
    ori        $2, $0, 0xFFFF;
    sltu       $2, $2, $7;
  L0013A500:
    bnez       $2, L0013A518;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $7, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013A52C;
    movn      $4, $0, $2;
  L0013A518:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $7;
    movn       $4, $3, $2;
  L0013A52C:
    srlv       $3, $7, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x76C8($2);
    addu       $2, $2, $4;
    subu       $12, $5, $2;
    bnez       $12, L0013A560;
    subu      $15, $5, $12;
    subu       $10, $10, $7;
    srl        $5, $7, 16;
    b          L0013A630;
    andi      $14, $7, 0xFFFF;
  L0013A560:
    sllv       $3, $10, $12;
    srlv       $2, $13, $15;
    sllv       $13, $13, $12;
    srlv       $4, $10, $15;
    or         $10, $3, $2;
    sllv       $7, $7, $12;
    srl        $5, $7, 16;
    divu $4, $5;
    srl        $4, $10, 16;
    andi       $14, $7, 0xFFFF;
    daddu      $9, $5, $0;
    beql       $9, $0, L0013A594;
        .word 0x000001CD;
  L0013A594:
    mflo       $2;
    mfhi       $3;
    mult       $8, $2, $14;
    sll        $3, $3, 16;
    or         $6, $3, $4;
    sltu       $2, $6, $8;
    beqz       $2, L0013A5D8;
    daddu     $15, $14, $0;
    addu       $6, $6, $7;
    sltu       $2, $6, $7;
    bnel       $2, $0, L0013A5DC;
    subu      $6, $6, $8;
    sltu       $2, $6, $8;
    addu       $3, $6, $7;
    xori       $2, $2, 0x0;
    movn       $6, $3, $2;
    nop;
  L0013A5D8:
    subu       $6, $6, $8;
  L0013A5DC:
    andi       $4, $10, 0xFFFF;
    divu $6, $9;
    beql       $9, $0, L0013A5EC;
        .word 0x000001CD;
  L0013A5EC:
    mflo       $2;
    mfhi       $3;
    mult       $8, $2, $15;
    sll        $3, $3, 16;
    or         $4, $3, $4;
    sltu       $2, $4, $8;
    beqz       $2, L0013A630;
    subu      $10, $4, $8;
    addu       $4, $4, $7;
    sltu       $2, $4, $7;
    bnez       $2, L0013A630;
    subu      $10, $4, $8;
    sltu       $2, $4, $8;
    addu       $3, $4, $7;
    xori       $2, $2, 0x0;
    movn       $4, $3, $2;
    subu       $10, $4, $8;
  L0013A630:
    daddu      $6, $5, $0;
    daddu      $9, $14, $0;
  L0013A638:
    divu $10, $6;
    srl        $4, $13, 16;
    beql       $6, $0, L0013A648;
        .word 0x000001CD;
  L0013A648:
    mflo       $2;
    mfhi       $3;
    mult       $8, $2, $9;
    sll        $3, $3, 16;
    or         $5, $3, $4;
    sltu       $2, $5, $8;
    beql       $2, $0, L0013A68C;
    subu      $5, $5, $8;
    addu       $5, $5, $7;
    sltu       $2, $5, $7;
    bnel       $2, $0, L0013A68C;
    subu      $5, $5, $8;
    sltu       $2, $5, $8;
    addu       $3, $5, $7;
    xori       $2, $2, 0x0;
    movn       $5, $3, $2;
    subu       $5, $5, $8;
  L0013A68C:
    andi       $4, $13, 0xFFFF;
    divu $5, $6;
    beql       $6, $0, L0013A69C;
        .word 0x000001CD;
  L0013A69C:
    mflo       $2;
    mfhi       $3;
    mult       $8, $2, $9;
    sll        $3, $3, 16;
    or         $4, $3, $4;
    sltu       $2, $4, $8;
    beqz       $2, L0013A6D8;
    nop;
    addu       $4, $4, $7;
    sltu       $2, $4, $7;
    bnez       $2, L0013A6D8;
    sltu      $2, $4, $8;
    addu       $3, $4, $7;
    xori       $2, $2, 0x0;
    movn       $4, $3, $2;
  L0013A6D8:
    beqz       $24, L0013A98C;
    subu      $13, $4, $8;
    srlv       $2, $13, $12;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    dsll32     $2, $2, 0;
    and        $11, $11, $3;
    dsrl32     $2, $2, 0;
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    or         $11, $11, $2;
    b          L0013A988;
    and       $11, $11, $3;
    nop;
  L0013A710:
    sltu       $2, $10, $9;
    beqz       $2, L0013A750;
    ori       $2, $0, 0xFFFF;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    dsll32     $2, $13, 0;
    dsrl32     $2, $2, 0;
    and        $11, $11, $3;
    or         $11, $11, $2;
    dsll32     $2, $10, 0;
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    and        $11, $11, $3;
    or         $11, $11, $2;
    b          L0013A98C;
    sd        $11, 0x0($29);
  L0013A750:
    sltu       $2, $2, $9;
    bnez       $2, L0013A770;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $9, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013A784;
    movn      $4, $0, $2;
    nop;
  L0013A770:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $9;
    movn       $4, $3, $2;
  L0013A784:
    srlv       $3, $9, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x76C8($2);
    addu       $2, $2, $4;
    subu       $12, $5, $2;
    bnez       $12, L0013A808;
    subu      $15, $5, $12;
    sltu       $2, $9, $10;
    bnez       $2, L0013A7C0;
    subu      $2, $13, $7;
    sltu       $2, $13, $7;
    bnez       $2, L0013A7D0;
    subu      $2, $13, $7;
  L0013A7C0:
    subu       $4, $10, $9;
    sltu       $3, $13, $2;
    daddu      $13, $2, $0;
    subu       $10, $4, $3;
  L0013A7D0:
    beqz       $24, L0013A98C;
    dsll32    $2, $13, 0;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    dsrl32     $2, $2, 0;
    and        $11, $11, $3;
    or         $11, $11, $2;
    dsll32     $2, $10, 0;
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    and        $11, $11, $3;
    b          L0013A988;
    or        $11, $11, $2;
    nop;
  L0013A808:
    sllv       $5, $10, $12;
    sllv       $4, $9, $12;
    srlv       $2, $7, $15;
    srlv       $3, $13, $15;
    sllv       $13, $13, $12;
    or         $9, $4, $2;
    srlv       $4, $10, $15;
    sllv       $7, $7, $12;
    or         $10, $5, $3;
    srl        $6, $9, 16;
    divu $4, $6;
    srl        $4, $10, 16;
    andi       $5, $9, 0xFFFF;
    beql       $6, $0, L0013A844;
        .word 0x000001CD;
  L0013A844:
    mflo       $2;
    mfhi       $3;
    daddu      $14, $2, $0;
    sll        $3, $3, 16;
    mult       $8, $14, $5;
    or         $3, $3, $4;
    sltu       $2, $3, $8;
    beql       $2, $0, L0013A894;
    subu      $3, $3, $8;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L0013A890;
    addiu     $14, $14, -0x1;
    sltu       $2, $3, $8;
    beql       $2, $0, L0013A894;
    subu      $3, $3, $8;
    addiu      $14, $14, -0x1;
    addu       $3, $3, $9;
    nop;
  L0013A890:
    subu       $3, $3, $8;
  L0013A894:
    beql       $6, $0, L0013A89C;
        .word 0x000001CD;
  L0013A89C:
    divu $3, $6;
    andi       $4, $10, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $8, $6, $5;
    or         $5, $3, $4;
    sltu       $2, $5, $8;
    beql       $2, $0, L0013A8F0;
    subu      $5, $5, $8;
    addu       $5, $5, $9;
    sltu       $2, $5, $9;
    bnez       $2, L0013A8EC;
    addiu     $6, $6, -0x1;
    sltu       $2, $5, $8;
    beql       $2, $0, L0013A8F0;
    subu      $5, $5, $8;
    addiu      $6, $6, -0x1;
    addu       $5, $5, $9;
  L0013A8EC:
    subu       $5, $5, $8;
  L0013A8F0:
    sll        $2, $14, 16;
    or         $2, $2, $6;
    daddu      $10, $5, $0;
    multu      $2, $7;
    mfhi       $6;
    mflo       $8;
    sltu       $3, $10, $6;
    bnez       $3, L0013A928;
    subu      $2, $8, $7;
    bne        $6, $10, L0013A938;
    sltu      $2, $13, $8;
    beqz       $2, L0013A938;
    subu      $2, $8, $7;
    nop;
  L0013A928:
    subu       $4, $6, $9;
    sltu       $3, $8, $2;
    daddu      $8, $2, $0;
    subu       $6, $4, $3;
  L0013A938:
    beqz       $24, L0013A98C;
    subu      $4, $13, $8;
    subu       $5, $5, $6;
    sltu       $3, $13, $4;
    subu       $10, $5, $3;
    sllv       $2, $10, $15;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    srlv       $4, $4, $12;
    and        $11, $11, $3;
    or         $2, $2, $4;
    lui        $4, (0xFFFF0000 >> 16);
    dsrl32     $4, $4, 0;
    dsll32     $2, $2, 0;
    srlv       $3, $10, $12;
    dsrl32     $2, $2, 0;
    dsll32     $3, $3, 0;
    or         $11, $11, $2;
    and        $11, $11, $4;
    or         $11, $11, $3;
  L0013A988:
    sd         $11, 0x0($24);
  L0013A98C:
    ld         $2, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

