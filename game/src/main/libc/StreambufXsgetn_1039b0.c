#include "types.h"

extern void memcpy(void);

asm void StreambufXsgetn_1039b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    daddu      $18, $4, $0;
    sq         $16, 0x0($29);
    daddu      $17, $5, $0;
    sd         $6, 0x40($29);
    lw         $3, 0xC($4);
    lw         $2, 0x8($4);
    subu       $2, $3, $2;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    slt        $1, $2, $6;
    beqz       $1, L001039F8;
    sd        $2, 0x48($29);
    b          L001039FC;
    addiu     $2, $29, 0x48;
  L001039F8:
    addiu      $2, $29, 0x40;
  L001039FC:
    ld         $16, 0x0($2);
    blezl      $16, L00103A44;
    ld        $2, 0x40($29);
    lw         $5, 0x8($18);
    dsll32     $6, $16, 0;
    dsra32     $6, $6, 0;
    jal        memcpy;
    daddu     $4, $17, $0;
    lw         $2, 0x8($18);
    dsll32     $3, $16, 0;
    dsra32     $3, $3, 0;
    addu       $17, $17, $3;
    addu       $2, $2, $3;
    sw         $2, 0x8($18);
    ld         $2, 0x40($29);
    dsubu      $2, $2, $16;
    sd         $2, 0x40($29);
    ld         $2, 0x40($29);
  L00103A44:
    blez       $2, L00103AA8;
    nop;
  L00103A4C:
    lw         $3, 0x8($18);
    lw         $2, 0xC($18);
    sltu       $1, $3, $2;
    beqz       $1, L00103A70;
    nop;
    addiu      $2, $3, 0x1;
    sw         $2, 0x8($18);
    b          L00103A80;
    lbu       $2, 0x0($3);
  L00103A70:
    lw         $25, 0x0($18);
    lw         $25, 0x28($25);
    jalr $31, $25;
    daddu     $4, $18, $0;
  L00103A80:
    addiu      $3, $0, -0x1;
    beq        $2, $3, L00103AA8;
    nop;
    sb         $2, 0x0($17);
    daddiu     $16, $16, 0x1;
    ld         $2, 0x40($29);
    addiu      $17, $17, 0x1;
    daddiu     $2, $2, -0x1;
    bgtz       $2, L00103A4C;
    sd        $2, 0x40($29);
  L00103AA8:
    daddu      $2, $16, $0;
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

