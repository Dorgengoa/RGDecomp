#include "types.h"

asm void MpegAddStrCallback_115740(void)
{
    .set noreorder;
    lw         $11, 0x40($4);
    daddu      $14, $6, $0;
    daddu      $12, $0, $0;
    daddu      $3, $0, $0;
    sltiu      $2, $5, 0xA;
    beqz       $2, L001157D8;
    lw        $10, 0x60($11);
    lui        $13, 0x44;
    sll        $9, $5, 4;
    addiu      $2, $13, 0x60C0;
    ori        $4, $0, 0xFFFF;
    dsll       $4, $4, 24;
    addu       $2, $2, $9;
    ld         $3, 0x8($2);
    beq        $3, $4, L001157B8;
    sltu      $2, $4, $3;
    bnez       $2, L001157A0;
    nop;
    ori        $2, $0, 0xFF00;
    dsll       $2, $2, 24;
    beq        $3, $2, L001157C0;
    daddu     $6, $0, $0;
    b          L001157E0;
    lw        $9, 0x64($11);
  L001157A0:
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 24;
    bne        $3, $2, L001157DC;
    daddu     $6, $0, $0;
    b          L001157C4;
    daddu     $6, $0, $0;
  L001157B8:
    b          L001157C4;
    addiu     $6, $0, 0x18;
  L001157C0:
    addiu      $6, $0, 0x20;
  L001157C4:
    addiu      $2, $13, 0x60C0;
    dsllv      $4, $14, $6;
    addu       $2, $9, $2;
    ld         $3, 0x0($2);
    or         $3, $3, $4;
  L001157D8:
    daddu      $6, $3, $0;
  L001157DC:
    lw         $9, 0x64($11);
  L001157E0:
    blez       $9, L00115820;
    daddu     $4, $0, $0;
    ld         $2, 0x0($10);
    bnel       $6, $2, L00115800;
    addiu     $4, $4, 0x1;
    b          L00115820;
    lw        $12, 0x10($10);
    nop;
  L00115800:
    slt        $2, $4, $9;
    beqz       $2, L00115820;
    sll       $2, $4, 5;
    addu       $2, $2, $10;
    ld         $3, 0x0($2);
    bnel       $6, $3, L00115800;
    addiu     $4, $4, 0x1;
    lw         $12, 0x10($2);
  L00115820:
    slti       $2, $4, 0x40;
    beqz       $2, L00115868;
    sll       $3, $4, 5;
    sll        $2, $5, 4;
    addu       $3, $3, $10;
    lui        $4, 0x44;
    addiu      $4, $4, 0x60C0;
    sd         $6, 0x0($3);
    addu       $4, $4, $2;
    sw         $7, 0x10($3);
    ld         $2, 0x8($4);
    sw         $8, 0x14($3);
    sd         $2, 0x8($3);
    daddu      $4, $28, $0;
    lw         $2, 0x64($11);
    sw         $4, 0x18($3);
    addiu      $2, $2, 0x1;
    sw         $2, 0x64($11);
  L00115868:
    jr         $31;
    daddu     $2, $12, $0;
}
