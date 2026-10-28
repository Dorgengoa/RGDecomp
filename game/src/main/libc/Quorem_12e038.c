#include "types.h"

extern void Mcmp_1325e0(void);

asm void Quorem_12e038(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    daddu      $14, $5, $0;
    sd         $20, 0x20($29);
    daddu      $20, $4, $0;
    sd         $16, 0x0($29);
    sd         $17, 0x8($29);
    sd         $18, 0x10($29);
    sd         $19, 0x18($29);
    sd         $21, 0x28($29);
    sd         $22, 0x30($29);
    sd         $31, 0x38($29);
    lw         $16, 0x10($14);
    lw         $3, 0x10($20);
    slt        $3, $3, $16;
    bnez       $3, L0012E23C;
    daddu     $2, $0, $0;
    addiu      $16, $16, -0x1;
    addiu      $11, $14, 0x14;
    sll        $2, $16, 2;
    addiu      $17, $20, 0x14;
    addu       $19, $11, $2;
    addu       $9, $17, $2;
    lw         $3, 0x0($19);
    daddu      $22, $11, $0;
    lw         $13, 0x0($9);
    daddu      $10, $17, $0;
    addiu      $3, $3, 0x1;
    divu $13, $3;
    beql       $3, $0, L0012E0B0;
        .word 0x000001CD;
  L0012E0B0:
    mflo       $21;
    daddu      $18, $21, $0;
    beqz       $18, L0012E168;
    daddu     $12, $0, $0;
    daddu      $3, $0, $0;
    nop;
  L0012E0C8:
    lw         $4, 0x0($11);
    addiu      $11, $11, 0x4;
    lw         $6, 0x0($10);
    sltu       $7, $19, $11;
    andi       $2, $4, 0xFFFF;
    srl        $4, $4, 16;
    mult       $5, $2, $18;
    mult       $4, $4, $18;
    addu       $2, $5, $3;
    andi       $3, $6, 0xFFFF;
    andi       $5, $2, 0xFFFF;
    srl        $2, $2, 16;
    addu       $8, $4, $2;
    subu       $3, $3, $5;
    addu       $3, $3, $12;
    srl        $6, $6, 16;
    andi       $2, $8, 0xFFFF;
    sra        $12, $3, 16;
    subu       $6, $6, $2;
    sh         $3, 0x0($10);
    addu       $5, $6, $12;
    srl        $3, $8, 16;
    sh         $5, 0x2($10);
    addiu      $10, $10, 0x4;
    beqz       $7, L0012E0C8;
    sra       $12, $5, 16;
    bnel       $13, $0, L0012E16C;
    daddu     $5, $14, $0;
    b          L0012E144;
    addiu     $9, $9, -0x4;
  L0012E140:
    addiu      $16, $16, -0x1;
  L0012E144:
    sltu       $2, $17, $9;
    beql       $2, $0, L0012E168;
    sw        $16, 0x10($20);
    lw         $2, 0x0($9);
    nop;
    nop;
    beql       $2, $0, L0012E140;
    addiu     $9, $9, -0x4;
    sw         $16, 0x10($20);
  L0012E168:
    daddu      $5, $14, $0;
  L0012E16C:
    jal        Mcmp_1325e0;
    daddu     $4, $20, $0;
    bltz       $2, L0012E238;
    daddu     $11, $22, $0;
    addiu      $18, $21, 0x1;
    daddu      $12, $0, $0;
    daddu      $3, $0, $0;
    daddu      $10, $17, $0;
    nop;
  L0012E190:
    lw         $4, 0x0($11);
    addiu      $11, $11, 0x4;
    lw         $5, 0x0($10);
    sltu       $7, $19, $11;
    andi       $2, $4, 0xFFFF;
    srl        $6, $4, 16;
    addu       $2, $2, $3;
    andi       $3, $5, 0xFFFF;
    andi       $4, $2, 0xFFFF;
    srl        $2, $2, 16;
    addu       $8, $6, $2;
    subu       $3, $3, $4;
    addu       $3, $3, $12;
    srl        $5, $5, 16;
    andi       $2, $8, 0xFFFF;
    sra        $12, $3, 16;
    subu       $5, $5, $2;
    sh         $3, 0x0($10);
    addu       $5, $5, $12;
    srl        $3, $8, 16;
    sh         $5, 0x2($10);
    addiu      $10, $10, 0x4;
    beqz       $7, L0012E190;
    sra       $12, $5, 16;
    sll        $2, $16, 2;
    addu       $9, $17, $2;
    lw         $3, 0x0($9);
    bnez       $3, L0012E23C;
    daddu     $2, $18, $0;
    b          L0012E214;
    addiu     $9, $9, -0x4;
    nop;
  L0012E210:
    addiu      $16, $16, -0x1;
  L0012E214:
    sltu       $2, $17, $9;
    beql       $2, $0, L0012E238;
    sw        $16, 0x10($20);
    lw         $2, 0x0($9);
    nop;
    nop;
    beql       $2, $0, L0012E210;
    addiu     $9, $9, -0x4;
    sw         $16, 0x10($20);
  L0012E238:
    daddu      $2, $18, $0;
  L0012E23C:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $21, 0x28($29);
    ld         $22, 0x30($29);
    ld         $31, 0x38($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

