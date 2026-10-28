#include "types.h"

asm void UDivDi3_139eb0(void)
{
    .set noreorder;
    dsra32     $8, $5, 0;
    dsra32     $10, $4, 0;
    dsll32     $9, $5, 0;
    dsra32     $9, $9, 0;
    dsll32     $11, $4, 0;
    dsra32     $11, $11, 0;
    bnez       $8, L0013A250;
    sltu      $2, $10, $8;
    sltu       $2, $10, $9;
    beqz       $2, L0013A010;
    ori       $2, $0, 0xFFFF;
    sltu       $2, $2, $9;
    bnez       $2, L00139EF8;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $9, 0x100;
    addiu      $4, $0, 0x8;
    b          L00139F0C;
    movn      $4, $0, $2;
  L00139EF8:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $9;
    movn       $4, $3, $2;
  L00139F0C:
    srlv       $3, $9, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x77C8($2);
    addu       $2, $2, $4;
    subu       $6, $5, $2;
    beqz       $6, L00139F44;
    subu      $2, $5, $6;
    sllv       $3, $10, $6;
    srlv       $2, $11, $2;
    sllv       $11, $11, $6;
    or         $10, $3, $2;
    sllv       $9, $9, $6;
  L00139F44:
    srl        $6, $9, 16;
    andi       $8, $9, 0xFFFF;
    divu $10, $6;
    srl        $4, $11, 16;
    beql       $6, $0, L00139F5C;
        .word 0x000001CD;
  L00139F5C:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $7, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beql       $2, $0, L00139FAC;
    subu      $3, $3, $5;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L00139FA8;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $5;
    beql       $2, $0, L00139FAC;
    subu      $3, $3, $5;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $9;
    nop;
  L00139FA8:
    subu       $3, $3, $5;
  L00139FAC:
    beql       $6, $0, L00139FB4;
        .word 0x000001CD;
  L00139FB4:
    divu $3, $6;
    andi       $4, $11, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $6, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L0013A004;
    sll       $2, $7, 16;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L0013A000;
    addiu     $6, $6, -0x1;
    sltu       $2, $3, $5;
    addiu      $3, $6, -0x1;
    xori       $2, $2, 0x0;
    movn       $6, $3, $2;
  L0013A000:
    sll        $2, $7, 16;
  L0013A004:
    b          L0013A3F8;
    or        $6, $2, $6;
    nop;
  L0013A010:
    bnez       $9, L0013A038;
    sltu      $2, $2, $9;
    addiu      $2, $0, 0x1;
    beql       $9, $0, L0013A024;
        .word 0x000001CD;
  L0013A024:
    divu $2, $8;
    mflo       $2;
    daddu      $9, $2, $0;
    ori        $2, $0, 0xFFFF;
    sltu       $2, $2, $9;
  L0013A038:
    bnez       $2, L0013A050;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $9, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013A064;
    movn      $4, $0, $2;
  L0013A050:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $9;
    movn       $4, $3, $2;
  L0013A064:
    srlv       $3, $9, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x77C8($2);
    addu       $2, $2, $4;
    subu       $6, $5, $2;
    bnez       $6, L0013A0A0;
    subu      $7, $5, $6;
    subu       $10, $10, $9;
    addiu      $13, $0, 0x1;
    srl        $8, $9, 16;
    b          L0013A188;
    andi      $12, $9, 0xFFFF;
    nop;
  L0013A0A0:
    sllv       $3, $10, $6;
    srlv       $2, $11, $7;
    sllv       $11, $11, $6;
    srlv       $4, $10, $7;
    or         $10, $3, $2;
    sllv       $9, $9, $6;
    srl        $8, $9, 16;
    divu $4, $8;
    srl        $4, $10, 16;
    andi       $12, $9, 0xFFFF;
    daddu      $6, $8, $0;
    beql       $6, $0, L0013A0D4;
        .word 0x000001CD;
  L0013A0D4:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $7, $12;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L0013A120;
    daddu     $13, $12, $0;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L0013A120;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $5;
    beql       $2, $0, L0013A124;
    subu      $3, $3, $5;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $9;
    nop;
  L0013A120:
    subu       $3, $3, $5;
  L0013A124:
    beql       $6, $0, L0013A12C;
        .word 0x000001CD;
  L0013A12C:
    divu $3, $6;
    andi       $4, $10, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $6, $13;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L0013A180;
    sll       $2, $7, 16;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L0013A17C;
    addiu     $6, $6, -0x1;
    sltu       $2, $3, $5;
    beqz       $2, L0013A180;
    sll       $2, $7, 16;
    addiu      $6, $6, -0x1;
    addu       $3, $3, $9;
  L0013A17C:
    sll        $2, $7, 16;
  L0013A180:
    subu       $10, $3, $5;
    or         $13, $2, $6;
  L0013A188:
    daddu      $6, $8, $0;
    daddu      $8, $12, $0;
    divu $10, $6;
    srl        $4, $11, 16;
    beql       $6, $0, L0013A1A0;
        .word 0x000001CD;
  L0013A1A0:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $7, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beql       $2, $0, L0013A1EC;
    subu      $3, $3, $5;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L0013A1E8;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $5;
    beql       $2, $0, L0013A1EC;
    subu      $3, $3, $5;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $9;
  L0013A1E8:
    subu       $3, $3, $5;
  L0013A1EC:
    beql       $6, $0, L0013A1F4;
        .word 0x000001CD;
  L0013A1F4:
    divu $3, $6;
    andi       $4, $11, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $6, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L0013A244;
    sll       $2, $7, 16;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L0013A240;
    addiu     $6, $6, -0x1;
    sltu       $2, $3, $5;
    addiu      $3, $6, -0x1;
    xori       $2, $2, 0x0;
    movn       $6, $3, $2;
  L0013A240:
    sll        $2, $7, 16;
  L0013A244:
    b          L0013A3FC;
    or        $6, $2, $6;
    nop;
  L0013A250:
    beql       $2, $0, L0013A260;
    ori       $2, $0, 0xFFFF;
    b          L0013A3F8;
    daddu     $6, $0, $0;
  L0013A260:
    sltu       $2, $2, $8;
    bnez       $2, L0013A280;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $8, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013A294;
    movn      $4, $0, $2;
    nop;
  L0013A280:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $8;
    movn       $4, $3, $2;
  L0013A294:
    srlv       $3, $8, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x77C8($2);
    addu       $2, $2, $4;
    subu       $6, $5, $2;
    bnez       $6, L0013A2D8;
    subu      $7, $5, $6;
    sltu       $2, $8, $10;
    bnez       $2, L0013A3F8;
    addiu     $6, $0, 0x1;
    sltu       $2, $11, $9;
    bnez       $2, L0013A3F8;
    daddu     $6, $0, $0;
    b          L0013A3F8;
    addiu     $6, $0, 0x1;
  L0013A2D8:
    sllv       $4, $8, $6;
    srlv       $5, $11, $7;
    sllv       $11, $11, $6;
    srlv       $2, $9, $7;
    sllv       $9, $9, $6;
    sllv       $3, $10, $6;
    or         $8, $4, $2;
    srlv       $4, $10, $7;
    or         $10, $3, $5;
    srl        $5, $8, 16;
    divu $4, $5;
    srl        $4, $10, 16;
    andi       $12, $8, 0xFFFF;
    beql       $5, $0, L0013A314;
        .word 0x000001CD;
  L0013A314:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $6, $7, $12;
    or         $3, $3, $4;
    sltu       $2, $3, $6;
    beql       $2, $0, L0013A364;
    subu      $3, $3, $6;
    addu       $3, $3, $8;
    sltu       $2, $3, $8;
    bnez       $2, L0013A360;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $6;
    beql       $2, $0, L0013A364;
    subu      $3, $3, $6;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $8;
    nop;
  L0013A360:
    subu       $3, $3, $6;
  L0013A364:
    beql       $5, $0, L0013A36C;
        .word 0x000001CD;
  L0013A36C:
    divu $3, $5;
    andi       $4, $10, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $5, $2, $0;
    sll        $3, $3, 16;
    mult       $6, $5, $12;
    or         $3, $3, $4;
    sltu       $2, $3, $6;
    beqz       $2, L0013A3C0;
    sll       $2, $7, 16;
    addu       $3, $3, $8;
    sltu       $2, $3, $8;
    bnez       $2, L0013A3BC;
    addiu     $5, $5, -0x1;
    sltu       $2, $3, $6;
    beqz       $2, L0013A3C0;
    sll       $2, $7, 16;
    addu       $3, $3, $8;
    addiu      $5, $5, -0x1;
  L0013A3BC:
    sll        $2, $7, 16;
  L0013A3C0:
    subu       $3, $3, $6;
    or         $6, $2, $5;
    multu      $6, $9;
    mfhi       $7;
    mflo       $4;
    sltu       $2, $3, $7;
    bnel       $2, $0, L0013A3F8;
    addiu     $6, $6, -0x1;
    bne        $7, $3, L0013A3FC;
    daddu     $13, $0, $0;
    sltu       $2, $11, $4;
    beqz       $2, L0013A3FC;
    nop;
    addiu      $6, $6, -0x1;
  L0013A3F8:
    daddu      $13, $0, $0;
  L0013A3FC:
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    dsll32     $2, $6, 0;
    dsrl32     $2, $2, 0;
    and        $14, $14, $3;
    or         $14, $14, $2;
    dsll32     $2, $13, 0;
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    and        $14, $14, $3;
    jr         $31;
    or        $2, $14, $2;
}

