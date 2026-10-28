#include "types.h"

asm void EhUnwindRestoreRegs_102770(void)
{
    .set noreorder;
    lw         $2, 0x4($5);
    lw         $8, 0x228($4);
    lb         $2, 0x0($2);
    lwu        $5, 0x220($4);
    andi       $3, $2, 0x40;
    beqz       $3, L001027DC;
    lwu       $9, 0x224($4);
    lwu        $7, 0x234($4);
    dsll32     $11, $9, 0;
    addiu      $2, $0, -0x10;
    lw         $10, 0x18($4);
    pcpyld     $6, $0, $2;
    dsll       $9, $7, 2;
    dsra32     $11, $11, 0;
    daddiu     $9, $9, 0xF;
    addu       $10, $10, $11;
    and        $6, $9, $6;
    dsll       $2, $8, 4;
    dsll32     $6, $6, 0;
    dsra32     $6, $6, 0;
    addu       $6, $10, $6;
    dsll32     $9, $6, 0;
    dsrl32     $9, $9, 0;
    daddu      $2, $9, $2;
    dsll32     $13, $2, 0;
    b          L001027FC;
    dsra32    $13, $13, 0;
  L001027DC:
    dsll32     $10, $9, 0;
    dsll       $2, $8, 4;
    lw         $9, 0x18($4);
    dsra32     $10, $10, 0;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addu       $9, $9, $10;
    addu       $13, $9, $2;
  L001027FC:
    lw         $9, 0x230($4);
    beql       $9, $0, L00102810;
    lw        $2, 0x0($13);
    addiu      $13, $13, 0x10;
    lw         $2, 0x0($13);
  L00102810:
    beql       $9, $0, L00102828;
    addiu     $9, $0, 0x9;
    addiu      $13, $13, -0x10;
    lq         $9, 0x0($13);
    b          L00102840;
    sq        $9, 0x200($4);
  L00102828:
    bnel       $8, $9, L00102844;
    dsll32    $9, $8, 0;
    addiu      $13, $13, -0x10;
    daddiu     $8, $8, -0x1;
    lq         $9, 0x0($13);
    sq         $9, 0x200($4);
  L00102840:
    dsll32     $9, $8, 0;
  L00102844:
    sltu       $1, $0, $8;
    dsra32     $9, $9, 0;
    daddu      $12, $0, $0;
    sll        $9, $9, 4;
    beqz       $1, L00102888;
    subu      $13, $13, $9;
    daddu      $11, $4, $0;
  L00102860:
    lq         $10, 0x0($13);
    addiu      $12, $12, 0x1;
    dsll32     $9, $12, 0;
    dsra32     $9, $9, 0;
    sq         $10, 0x120($11);
    sltu       $9, $9, $8;
    addiu      $13, $13, 0x10;
    bnez       $9, L00102860;
    addiu     $11, $11, 0x10;
    nop;
  L00102888:
    dsll32     $8, $5, 0;
    lw         $5, 0x18($4);
    dsra32     $8, $8, 0;
    addu       $5, $5, $8;
    beqz       $3, L001028E0;
    sw        $5, 0x14($4);
    dsll32     $3, $7, 0;
    sltu       $1, $0, $7;
    dsra32     $3, $3, 0;
    daddu      $8, $0, $0;
    sll        $3, $3, 2;
    beqz       $1, L001028E0;
    subu      $6, $6, $3;
  L001028BC:
    lw         $5, 0x0($6);
    addiu      $8, $8, 0x1;
    dsll32     $3, $8, 0;
    dsra32     $3, $3, 0;
    sw         $5, 0x288($4);
    sltu       $3, $3, $7;
    addiu      $6, $6, 0x4;
    bnez       $3, L001028BC;
    addiu     $4, $4, 0x4;
  L001028E0:
    jr         $31;
    nop;
}

