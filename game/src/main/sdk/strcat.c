#include "types.h"

extern void strcpy(void);

asm void strcat(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sq         $16, 0x0($29);
    daddu      $16, $4, $0;
    andi       $2, $16, 0x7;
    bnez       $2, L00134784;
    sq        $31, 0x10($29);
    andi       $2, $16, 0xF;
    lui        $3, (0x1010101 >> 16);
    ori        $3, $3, (0x1010101 & 0xFFFF);
    dsll       $3, $3, 16;
    ori        $3, $3, 0x101;
    dsll       $3, $3, 16;
    ori        $3, $3, 0x101;
    lui        $4, (0x80808080 >> 16);
    ori        $4, $4, (0x80808080 & 0xFFFF);
    dsll       $4, $4, 16;
    ori        $4, $4, 0x8080;
    dsll       $4, $4, 16;
    ori        $4, $4, 0x8080;
    bnez       $2, L00134740;
    ld        $6, 0x0($16);
    lq         $2, 0x0($16);
    pcpyld     $7, $3, $3;
    pcpyld     $8, $4, $4;
    psubb      $3, $2, $7;
    pnor       $2, $0, $2;
    pand       $3, $3, $2;
    pand       $3, $3, $8;
    pcpyud     $2, $3, $3;
    or         $3, $2, $3;
    bnez       $3, L00134784;
    daddu     $4, $16, $0;
    addiu      $6, $4, 0x10;
  L00134714:
    lq         $2, 0x0($6);
    pnor       $3, $0, $2;
    psubb      $2, $2, $7;
    pand       $2, $2, $3;
    pand       $2, $2, $8;
    pcpyud     $3, $2, $2;
    or         $2, $2, $3;
    beql       $2, $0, L00134714;
    addiu     $6, $6, 0x10;
    b          L00134784;
    daddu     $4, $6, $0;
  L00134740:
    daddu      $7, $3, $0;
    daddu      $8, $4, $0;
    dsubu      $3, $6, $3;
    nor        $2, $0, $6;
    and        $3, $3, $2;
    and        $3, $3, $4;
    bnez       $3, L00134784;
    daddu     $4, $16, $0;
    addiu      $6, $16, 0x8;
  L00134764:
    ld         $2, 0x0($6);
    nor        $3, $0, $2;
    dsubu      $2, $2, $7;
    and        $2, $2, $3;
    and        $2, $2, $8;
    beql       $2, $0, L00134764;
    addiu     $6, $6, 0x8;
    daddu      $4, $6, $0;
  L00134784:
    lb         $2, 0x0($4);
    nop;
    nop;
    nop;
    nop;
    bnel       $2, $0, L00134784;
    addiu     $4, $4, 0x1;
    jal        strcpy;
    nop;
    daddu      $2, $16, $0;
    lq         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

