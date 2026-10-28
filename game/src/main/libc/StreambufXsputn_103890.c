#include "types.h"

extern void memcpy(void);

asm void StreambufXsputn_103890(void)
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
    lw         $3, 0x18($4);
    lw         $2, 0x14($4);
    subu       $2, $3, $2;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    slt        $1, $2, $6;
    beqz       $1, L001038D8;
    sd        $2, 0x48($29);
    b          L001038DC;
    addiu     $2, $29, 0x48;
  L001038D8:
    addiu      $2, $29, 0x40;
  L001038DC:
    ld         $16, 0x0($2);
    blezl      $16, L00103924;
    ld        $2, 0x40($29);
    lw         $4, 0x14($18);
    dsll32     $6, $16, 0;
    dsra32     $6, $6, 0;
    jal        memcpy;
    daddu     $5, $17, $0;
    lw         $2, 0x14($18);
    dsll32     $3, $16, 0;
    dsra32     $3, $3, 0;
    addu       $17, $17, $3;
    addu       $2, $2, $3;
    sw         $2, 0x14($18);
    ld         $2, 0x40($29);
    dsubu      $2, $2, $16;
    sd         $2, 0x40($29);
    ld         $2, 0x40($29);
  L00103924:
    blez       $2, L00103990;
    nop;
  L0010392C:
    lw         $3, 0x14($18);
    lw         $2, 0x18($18);
    lb         $4, 0x0($17);
    sltu       $1, $3, $2;
    beqz       $1, L00103958;
    addiu     $17, $17, 0x1;
    addiu      $2, $3, 0x1;
    sw         $2, 0x14($18);
    sb         $4, 0x0($3);
    b          L00103970;
    lbu       $2, 0x0($3);
  L00103958:
    lw         $25, 0x0($18);
    andi       $5, $4, 0xFF;
    lw         $25, 0x34($25);
    jalr $31, $25;
    daddu     $4, $18, $0;
    nop;
  L00103970:
    addiu      $3, $0, -0x1;
    beq        $2, $3, L00103990;
    nop;
    ld         $2, 0x40($29);
    daddiu     $16, $16, 0x1;
    daddiu     $2, $2, -0x1;
    bgtz       $2, L0010392C;
    sd        $2, 0x40($29);
  L00103990:
    daddu      $2, $16, $0;
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

