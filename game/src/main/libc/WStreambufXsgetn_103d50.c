#include "types.h"

asm void WStreambufXsgetn_103d50(void)
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
    subu       $3, $3, $2;
    bgez       $3, L00103D8C;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L00103D8C:
    dsll32     $3, $2, 0;
    ld         $2, 0x40($29);
    dsra32     $3, $3, 0;
    slt        $1, $3, $2;
    beqz       $1, L00103DAC;
    sd        $3, 0x48($29);
    b          L00103DB0;
    addiu     $2, $29, 0x48;
  L00103DAC:
    addiu      $2, $29, 0x40;
  L00103DB0:
    ld         $16, 0x0($2);
    blezl      $16, L00103EA4;
    ld        $2, 0x40($29);
    dsll32     $2, $16, 0;
    lw         $8, 0x8($18);
    dsra32     $2, $2, 0;
    daddu      $9, $17, $0;
    beqz       $2, L00103E78;
    daddu     $7, $0, $0;
    sltiu      $1, $2, 0x9;
    bnez       $1, L00103E40;
    addiu     $6, $2, -0x8;
  L00103DE0:
    lhu        $5, 0x0($8);
    addiu      $7, $7, 0x8;
    addiu      $3, $8, 0x1C;
    addiu      $4, $9, 0x1C;
    sltu       $2, $7, $6;
    sh         $5, 0x0($9);
    lhu        $5, 0x4($8);
    sh         $5, 0x4($9);
    lhu        $5, 0x8($8);
    sh         $5, 0x8($9);
    lhu        $5, 0xC($8);
    sh         $5, 0xC($9);
    lhu        $5, 0x10($8);
    sh         $5, 0x10($9);
    lhu        $5, 0x14($8);
    sh         $5, 0x14($9);
    lhu        $5, 0x18($8);
    sh         $5, 0x18($9);
    addiu      $8, $8, 0x20;
    lhu        $3, 0x0($3);
    addiu      $9, $9, 0x20;
    bnez       $2, L00103DE0;
    sh        $3, 0x0($4);
    nop;
  L00103E40:
    dsll32     $4, $16, 0;
    dsra32     $4, $4, 0;
    sltu       $1, $7, $4;
    beqz       $1, L00103E78;
    nop;
  L00103E54:
    lhu        $3, 0x0($8);
    daddu      $5, $9, $0;
    addiu      $7, $7, 0x1;
    addiu      $9, $9, 0x4;
    sltu       $2, $7, $4;
    addiu      $8, $8, 0x4;
    bnez       $2, L00103E54;
    sh        $3, 0x0($5);
    nop;
  L00103E78:
    dsll32     $2, $16, 0;
    dsra32     $2, $2, 0;
    sll        $3, $2, 2;
    lw         $2, 0x8($18);
    addu       $17, $17, $3;
    addu       $2, $2, $3;
    sw         $2, 0x8($18);
    ld         $2, 0x40($29);
    dsubu      $2, $2, $16;
    sd         $2, 0x40($29);
    ld         $2, 0x40($29);
  L00103EA4:
    blez       $2, L00103F08;
    nop;
  L00103EAC:
    lw         $3, 0x8($18);
    lw         $2, 0xC($18);
    sltu       $1, $3, $2;
    beqz       $1, L00103ED0;
    nop;
    addiu      $2, $3, 0x4;
    sw         $2, 0x8($18);
    b          L00103EE0;
    lhu       $2, 0x0($3);
  L00103ED0:
    lw         $25, 0x0($18);
    lw         $25, 0x28($25);
    jalr $31, $25;
    daddu     $4, $18, $0;
  L00103EE0:
    addiu      $3, $0, -0x1;
    beq        $2, $3, L00103F08;
    nop;
    sh         $2, 0x0($17);
    daddiu     $16, $16, 0x1;
    ld         $2, 0x40($29);
    addiu      $17, $17, 0x4;
    daddiu     $2, $2, -0x1;
    bgtz       $2, L00103EAC;
    sd        $2, 0x40($29);
  L00103F08:
    daddu      $2, $16, $0;
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

