#include "types.h"

extern void Swsetup_139000(void);
extern void memmove(void);
extern void Fflush_12f590(void);
extern void memchr(void);

asm void Sfvwrite_130478(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    daddu      $2, $0, $0;
    sd         $17, 0x8($29);
    sd         $22, 0x30($29);
    daddu      $22, $5, $0;
    sd         $16, 0x0($29);
    sd         $18, 0x10($29);
    sd         $19, 0x18($29);
    sd         $20, 0x20($29);
    sd         $21, 0x28($29);
    sd         $23, 0x38($29);
    sd         $31, 0x40($29);
    lw         $18, 0x8($22);
    beqz       $18, L0013082C;
    daddu     $17, $4, $0;
    lhu        $3, 0xC($17);
    andi       $2, $3, 0x8;
    beqz       $2, L001304D0;
    nop;
    lw         $2, 0x10($17);
    bnez       $2, L001304E8;
    andi      $2, $3, 0x2;
  L001304D0:
    jal        Swsetup_139000;
    nop;
    bnez       $2, L0013082C;
    addiu     $2, $0, -0x1;
    lhu        $3, 0xC($17);
    andi       $2, $3, 0x2;
  L001304E8:
    lw         $20, 0x0($22);
    beqz       $2, L00130568;
    daddu     $18, $0, $0;
    addiu      $21, $0, 0x400;
  L001304F8:
    bnel       $18, $0, L00130520;
    sltiu     $3, $18, 0x401;
  L00130500:
    lw         $18, 0x4($20);
    lw         $19, 0x0($20);
    nop;
    nop;
    nop;
    beqz       $18, L00130500;
    addiu     $20, $20, 0x8;
    sltiu      $3, $18, 0x401;
  L00130520:
    lw         $2, 0x24($17);
    lw         $4, 0x1C($17);
    daddu      $6, $21, $0;
    movn       $6, $18, $3;
    jalr $31, $2;
    daddu     $5, $19, $0;
    daddu      $16, $2, $0;
    blezl      $16, L00130820;
    lhu       $3, 0xC($17);
    lw         $2, 0x8($22);
    addu       $19, $19, $16;
    subu       $18, $18, $16;
    subu       $2, $2, $16;
    bnez       $2, L001304F8;
    sw        $2, 0x8($22);
    b          L0013082C;
    daddu     $2, $0, $0;
    nop;
  L00130568:
    andi       $2, $3, 0x1;
    bnez       $2, L001306B8;
    daddu     $23, $0, $0;
    b          L00130588;
    nop;
    nop;
  L00130580:
    lhu        $3, 0xC($17);
    nop;
  L00130588:
    bnez       $18, L001305B0;
    andi      $2, $3, 0x200;
  L00130590:
    lw         $18, 0x4($20);
    lw         $19, 0x0($20);
    nop;
    nop;
    nop;
    beqz       $18, L00130590;
    addiu     $20, $20, 0x8;
    andi       $2, $3, 0x200;
  L001305B0:
    beqz       $2, L001305E8;
    lw        $16, 0x8($17);
    sltu       $2, $18, $16;
    lw         $4, 0x0($17);
    movn       $16, $18, $2;
    daddu      $5, $19, $0;
    jal        memmove;
    daddu     $6, $16, $0;
    lw         $3, 0x8($17);
    lw         $2, 0x0($17);
    subu       $3, $3, $16;
    addu       $2, $2, $16;
    b          L0013068C;
    daddu     $16, $18, $0;
  L001305E8:
    lw         $4, 0x0($17);
    lw         $2, 0x10($17);
    sltu       $2, $2, $4;
    beql       $2, $0, L00130638;
    lw        $16, 0x14($17);
    sltu       $2, $16, $18;
    beql       $2, $0, L00130638;
    lw        $16, 0x14($17);
    daddu      $5, $19, $0;
    jal        memmove;
    daddu     $6, $16, $0;
    lw         $3, 0x0($17);
    daddu      $4, $17, $0;
    addu       $3, $3, $16;
    jal        Fflush_12f590;
    sw        $3, 0x0($17);
    beql       $2, $0, L00130698;
    lw        $2, 0x8($22);
    b          L00130820;
    lhu       $3, 0xC($17);
  L00130638:
    sltu       $2, $18, $16;
    bnel       $2, $0, L00130670;
    daddu     $16, $18, $0;
    lw         $2, 0x24($17);
    daddu      $6, $16, $0;
    lw         $4, 0x1C($17);
    jalr $31, $2;
    daddu     $5, $19, $0;
    daddu      $16, $2, $0;
    bgtzl      $16, L00130698;
    lw        $2, 0x8($22);
    b          L00130820;
    lhu       $3, 0xC($17);
    nop;
  L00130670:
    daddu      $5, $19, $0;
    jal        memmove;
    daddu     $6, $16, $0;
    lw         $3, 0x8($17);
    lw         $2, 0x0($17);
    subu       $3, $3, $16;
    addu       $2, $2, $16;
  L0013068C:
    sw         $3, 0x8($17);
    sw         $2, 0x0($17);
    lw         $2, 0x8($22);
  L00130698:
    addu       $19, $19, $16;
    subu       $18, $18, $16;
    subu       $2, $2, $16;
    bnez       $2, L00130580;
    sw        $2, 0x8($22);
    b          L0013082C;
    daddu     $2, $0, $0;
    nop;
  L001306B8:
    bnez       $18, L001306E4;
    nop;
    daddu      $23, $0, $0;
    nop;
  L001306C8:
    lw         $18, 0x4($20);
    lw         $19, 0x0($20);
    nop;
    nop;
    nop;
    beqz       $18, L001306C8;
    addiu     $20, $20, 0x8;
  L001306E4:
    bnel       $23, $0, L0013071C;
    lw        $8, 0x0($17);
    daddu      $4, $19, $0;
    addiu      $5, $0, 0xA;
    jal        memchr;
    daddu     $6, $18, $0;
    beqz       $2, L00130710;
    subu      $2, $2, $19;
    b          L00130714;
    addiu     $21, $2, 0x1;
    nop;
  L00130710:
    addiu      $21, $18, 0x1;
  L00130714:
    addiu      $23, $0, 0x1;
    lw         $8, 0x0($17);
  L0013071C:
    sltu       $2, $18, $21;
    lw         $3, 0x10($17);
    daddu      $5, $18, $0;
    lw         $4, 0x8($17);
    movz       $5, $21, $2;
    lw         $7, 0x14($17);
    sltu       $3, $3, $8;
    beqz       $3, L00130780;
    addu      $16, $4, $7;
    slt        $2, $16, $5;
    beql       $2, $0, L00130784;
    daddu     $16, $7, $0;
    daddu      $4, $8, $0;
    daddu      $5, $19, $0;
    jal        memmove;
    daddu     $6, $16, $0;
    lw         $3, 0x0($17);
    daddu      $4, $17, $0;
    addu       $3, $3, $16;
    jal        Fflush_12f590;
    sw        $3, 0x0($17);
    beqz       $2, L001307E4;
    subu      $21, $21, $16;
    b          L00130820;
    lhu       $3, 0xC($17);
  L00130780:
    daddu      $16, $7, $0;
  L00130784:
    slt        $2, $5, $16;
    bnel       $2, $0, L001307B8;
    daddu     $16, $5, $0;
    lw         $2, 0x24($17);
    daddu      $6, $16, $0;
    lw         $4, 0x1C($17);
    jalr $31, $2;
    daddu     $5, $19, $0;
    daddu      $16, $2, $0;
    bgtz       $16, L001307E4;
    subu      $21, $21, $16;
    b          L00130820;
    lhu       $3, 0xC($17);
  L001307B8:
    daddu      $5, $19, $0;
    daddu      $4, $8, $0;
    jal        memmove;
    daddu     $6, $16, $0;
    lw         $3, 0x8($17);
    lw         $2, 0x0($17);
    subu       $3, $3, $16;
    addu       $2, $2, $16;
    sw         $3, 0x8($17);
    sw         $2, 0x0($17);
    subu       $21, $21, $16;
  L001307E4:
    bnel       $21, $0, L00130804;
    lw        $2, 0x8($22);
    jal        Fflush_12f590;
    daddu     $4, $17, $0;
    bnel       $2, $0, L00130820;
    lhu       $3, 0xC($17);
    daddu      $23, $0, $0;
    lw         $2, 0x8($22);
  L00130804:
    addu       $19, $19, $16;
    subu       $18, $18, $16;
    subu       $2, $2, $16;
    bnez       $2, L001306B8;
    sw        $2, 0x8($22);
    b          L0013082C;
    daddu     $2, $0, $0;
  L00130820:
    addiu      $2, $0, -0x1;
    ori        $3, $3, 0x40;
    sh         $3, 0xC($17);
  L0013082C:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $21, 0x28($29);
    ld         $22, 0x30($29);
    ld         $23, 0x38($29);
    ld         $31, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

