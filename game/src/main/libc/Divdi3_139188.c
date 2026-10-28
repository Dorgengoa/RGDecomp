#include "types.h"

asm void Divdi3_139188(void)
{
    .set noreorder;
    daddu      $9, $4, $0;
    dsra32     $10, $9, 0;
    dsll32     $4, $10, 0;
    dsra32     $4, $4, 0;
    bgez       $4, L001391F4;
    daddu     $24, $0, $0;
    dsll32     $2, $9, 0;
    dsra32     $2, $2, 0;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    negu       $2, $2;
    and        $6, $6, $3;
    dsll32     $2, $2, 0;
    negu       $3, $4;
    dsrl32     $2, $2, 0;
    lui        $4, (0xFFFF0000 >> 16);
    dsrl32     $4, $4, 0;
    or         $6, $6, $2;
    addiu      $24, $0, -0x1;
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    and        $6, $6, $4;
    sltu       $2, $0, $2;
    subu       $3, $3, $2;
    dsll32     $3, $3, 0;
    or         $9, $6, $3;
    dsra32     $10, $9, 0;
  L001391F4:
    dsra32     $4, $5, 0;
    bgez       $4, L00139250;
    nop;
    dsll32     $2, $5, 0;
    dsra32     $2, $2, 0;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    negu       $2, $2;
    and        $7, $7, $3;
    dsll32     $2, $2, 0;
    negu       $3, $4;
    dsrl32     $2, $2, 0;
    lui        $4, (0xFFFF0000 >> 16);
    dsrl32     $4, $4, 0;
    or         $7, $7, $2;
    nor        $24, $0, $24;
    dsll32     $2, $7, 0;
    dsra32     $2, $2, 0;
    and        $7, $7, $4;
    sltu       $2, $0, $2;
    subu       $3, $3, $2;
    dsll32     $3, $3, 0;
    or         $5, $7, $3;
  L00139250:
    dsra32     $8, $5, 0;
    dsll32     $11, $9, 0;
    dsra32     $11, $11, 0;
    dsll32     $10, $10, 0;
    dsra32     $10, $10, 0;
    dsll32     $9, $5, 0;
    dsra32     $9, $9, 0;
    bnez       $8, L001395F8;
    sltu      $2, $10, $8;
    sltu       $2, $10, $9;
    beqz       $2, L001393B8;
    ori       $2, $0, 0xFFFF;
    sltu       $2, $2, $9;
    bnez       $2, L001392A0;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $9, 0x100;
    addiu      $4, $0, 0x8;
    b          L001392B4;
    movn      $4, $0, $2;
    nop;
  L001392A0:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $9;
    movn       $4, $3, $2;
  L001392B4:
    srlv       $3, $9, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x79C8($2);
    addu       $2, $2, $4;
    subu       $6, $5, $2;
    beqz       $6, L001392EC;
    subu      $2, $5, $6;
    sllv       $3, $10, $6;
    srlv       $2, $11, $2;
    sllv       $11, $11, $6;
    or         $10, $3, $2;
    sllv       $9, $9, $6;
  L001392EC:
    srl        $6, $9, 16;
    andi       $8, $9, 0xFFFF;
    divu $10, $6;
    srl        $4, $11, 16;
    beql       $6, $0, L00139304;
        .word 0x000001CD;
  L00139304:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $7, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beql       $2, $0, L00139354;
    subu      $3, $3, $5;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L00139350;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $5;
    beql       $2, $0, L00139354;
    subu      $3, $3, $5;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $9;
    nop;
  L00139350:
    subu       $3, $3, $5;
  L00139354:
    beql       $6, $0, L0013935C;
        .word 0x000001CD;
  L0013935C:
    divu $3, $6;
    andi       $4, $11, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $6, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L001393AC;
    sll       $2, $7, 16;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L001393A8;
    addiu     $6, $6, -0x1;
    sltu       $2, $3, $5;
    addiu      $3, $6, -0x1;
    xori       $2, $2, 0x0;
    movn       $6, $3, $2;
  L001393A8:
    sll        $2, $7, 16;
  L001393AC:
    b          L001397A0;
    or        $6, $2, $6;
    nop;
  L001393B8:
    bnez       $9, L001393E0;
    sltu      $2, $2, $9;
    addiu      $2, $0, 0x1;
    beql       $9, $0, L001393CC;
        .word 0x000001CD;
  L001393CC:
    divu $2, $8;
    mflo       $2;
    daddu      $9, $2, $0;
    ori        $2, $0, 0xFFFF;
    sltu       $2, $2, $9;
  L001393E0:
    bnez       $2, L001393F8;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $9, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013940C;
    movn      $4, $0, $2;
  L001393F8:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $9;
    movn       $4, $3, $2;
  L0013940C:
    srlv       $3, $9, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x79C8($2);
    addu       $2, $2, $4;
    subu       $6, $5, $2;
    bnez       $6, L00139448;
    subu      $7, $5, $6;
    subu       $10, $10, $9;
    addiu      $13, $0, 0x1;
    srl        $8, $9, 16;
    b          L00139530;
    andi      $12, $9, 0xFFFF;
    nop;
  L00139448:
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
    beql       $6, $0, L0013947C;
        .word 0x000001CD;
  L0013947C:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $7, $12;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L001394C8;
    daddu     $13, $12, $0;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L001394C8;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $5;
    beql       $2, $0, L001394CC;
    subu      $3, $3, $5;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $9;
    nop;
  L001394C8:
    subu       $3, $3, $5;
  L001394CC:
    beql       $6, $0, L001394D4;
        .word 0x000001CD;
  L001394D4:
    divu $3, $6;
    andi       $4, $10, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $6, $13;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L00139528;
    sll       $2, $7, 16;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L00139524;
    addiu     $6, $6, -0x1;
    sltu       $2, $3, $5;
    beqz       $2, L00139528;
    sll       $2, $7, 16;
    addiu      $6, $6, -0x1;
    addu       $3, $3, $9;
  L00139524:
    sll        $2, $7, 16;
  L00139528:
    subu       $10, $3, $5;
    or         $13, $2, $6;
  L00139530:
    daddu      $6, $8, $0;
    daddu      $8, $12, $0;
    divu $10, $6;
    srl        $4, $11, 16;
    beql       $6, $0, L00139548;
        .word 0x000001CD;
  L00139548:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $7, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beql       $2, $0, L00139594;
    subu      $3, $3, $5;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L00139590;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $5;
    beql       $2, $0, L00139594;
    subu      $3, $3, $5;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $9;
  L00139590:
    subu       $3, $3, $5;
  L00139594:
    beql       $6, $0, L0013959C;
        .word 0x000001CD;
  L0013959C:
    divu $3, $6;
    andi       $4, $11, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $6, $2, $0;
    sll        $3, $3, 16;
    mult       $5, $6, $8;
    or         $3, $3, $4;
    sltu       $2, $3, $5;
    beqz       $2, L001395EC;
    sll       $2, $7, 16;
    addu       $3, $3, $9;
    sltu       $2, $3, $9;
    bnez       $2, L001395E8;
    addiu     $6, $6, -0x1;
    sltu       $2, $3, $5;
    addiu      $3, $6, -0x1;
    xori       $2, $2, 0x0;
    movn       $6, $3, $2;
  L001395E8:
    sll        $2, $7, 16;
  L001395EC:
    b          L001397A4;
    or        $6, $2, $6;
    nop;
  L001395F8:
    beqz       $2, L00139608;
    ori       $2, $0, 0xFFFF;
    b          L001397A0;
    daddu     $6, $0, $0;
  L00139608:
    sltu       $2, $2, $8;
    bnez       $2, L00139628;
    lui       $2, (0xFFFFFF >> 16);
    sltiu      $2, $8, 0x100;
    addiu      $4, $0, 0x8;
    b          L0013963C;
    movn      $4, $0, $2;
    nop;
  L00139628:
    addiu      $3, $0, 0x18;
    ori        $2, $2, (0xFFFFFF & 0xFFFF);
    addiu      $4, $0, 0x10;
    sltu       $2, $2, $8;
    movn       $4, $3, $2;
  L0013963C:
    srlv       $3, $8, $4;
    addiu      $5, $0, 0x20;
    lui        $2, 0x46;
    addu       $2, $2, $3;
    lbu        $2, -0x79C8($2);
    addu       $2, $2, $4;
    subu       $6, $5, $2;
    bnez       $6, L00139680;
    subu      $7, $5, $6;
    sltu       $2, $8, $10;
    bnez       $2, L001397A0;
    addiu     $6, $0, 0x1;
    sltu       $2, $11, $9;
    bnez       $2, L001397A0;
    daddu     $6, $0, $0;
    b          L001397A0;
    addiu     $6, $0, 0x1;
  L00139680:
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
    beql       $5, $0, L001396BC;
        .word 0x000001CD;
  L001396BC:
    mflo       $2;
    mfhi       $3;
    daddu      $7, $2, $0;
    sll        $3, $3, 16;
    mult       $6, $7, $12;
    or         $3, $3, $4;
    sltu       $2, $3, $6;
    beql       $2, $0, L0013970C;
    subu      $3, $3, $6;
    addu       $3, $3, $8;
    sltu       $2, $3, $8;
    bnez       $2, L00139708;
    addiu     $7, $7, -0x1;
    sltu       $2, $3, $6;
    beql       $2, $0, L0013970C;
    subu      $3, $3, $6;
    addiu      $7, $7, -0x1;
    addu       $3, $3, $8;
    nop;
  L00139708:
    subu       $3, $3, $6;
  L0013970C:
    beql       $5, $0, L00139714;
        .word 0x000001CD;
  L00139714:
    divu $3, $5;
    andi       $4, $10, 0xFFFF;
    mflo       $2;
    mfhi       $3;
    daddu      $5, $2, $0;
    sll        $3, $3, 16;
    mult       $6, $5, $12;
    or         $3, $3, $4;
    sltu       $2, $3, $6;
    beqz       $2, L00139768;
    sll       $2, $7, 16;
    addu       $3, $3, $8;
    sltu       $2, $3, $8;
    bnez       $2, L00139764;
    addiu     $5, $5, -0x1;
    sltu       $2, $3, $6;
    beqz       $2, L00139768;
    sll       $2, $7, 16;
    addu       $3, $3, $8;
    addiu      $5, $5, -0x1;
  L00139764:
    sll        $2, $7, 16;
  L00139768:
    subu       $3, $3, $6;
    or         $6, $2, $5;
    multu      $6, $9;
    mfhi       $7;
    mflo       $4;
    sltu       $2, $3, $7;
    bnel       $2, $0, L001397A0;
    addiu     $6, $6, -0x1;
    bne        $7, $3, L001397A4;
    daddu     $13, $0, $0;
    sltu       $2, $11, $4;
    beqz       $2, L001397A8;
    dsll32    $2, $6, 0;
    addiu      $6, $6, -0x1;
  L001397A0:
    daddu      $13, $0, $0;
  L001397A4:
    dsll32     $2, $6, 0;
  L001397A8:
    addiu      $4, $0, -0x1;
    dsll32     $4, $4, 0;
    dsrl32     $2, $2, 0;
    and        $15, $15, $4;
    or         $15, $15, $2;
    dsll32     $2, $13, 0;
    lui        $5, (0xFFFF0000 >> 16);
    dsrl32     $5, $5, 0;
    and        $15, $15, $5;
    beqz       $24, L00139814;
    or        $3, $15, $2;
    dsll32     $2, $3, 0;
    dsra32     $2, $2, 0;
    and        $14, $14, $4;
    negu       $2, $2;
    dsra32     $4, $3, 0;
    dsll32     $2, $2, 0;
    negu       $4, $4;
    dsrl32     $2, $2, 0;
    or         $14, $14, $2;
    dsll32     $3, $14, 0;
    dsra32     $3, $3, 0;
    and        $14, $14, $5;
    sltu       $3, $0, $3;
    subu       $4, $4, $3;
    dsll32     $4, $4, 0;
    or         $3, $14, $4;
  L00139814:
    jr         $31;
    daddu     $2, $3, $0;
}

