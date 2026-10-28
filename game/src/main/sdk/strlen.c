#include "types.h"

asm void strlen(void)
{
    .set noreorder;
    andi       $2, $4, 0x7;
    bnez       $2, L00134CC4;
    daddu     $7, $4, $0;
    andi       $3, $4, 0xF;
    lui        $2, (0x1010101 >> 16);
    ori        $2, $2, (0x1010101 & 0xFFFF);
    dsll       $2, $2, 16;
    ori        $2, $2, 0x101;
    dsll       $2, $2, 16;
    ori        $2, $2, 0x101;
    bnez       $3, L00134C54;
    daddu     $5, $4, $0;
    lq         $3, 0x0($5);
    pcpyld     $8, $2, $2;
    lui        $4, (0x80808080 >> 16);
    ori        $4, $4, (0x80808080 & 0xFFFF);
    dsll       $4, $4, 16;
    ori        $4, $4, 0x8080;
    dsll       $4, $4, 16;
    ori        $4, $4, 0x8080;
    psubb      $2, $3, $8;
    pnor       $3, $0, $3;
    pcpyld     $9, $4, $4;
    pand       $2, $2, $3;
    pand       $2, $2, $9;
    pcpyud     $3, $2, $8;
    or         $6, $3, $2;
    bnel       $6, $0, L00134CC4;
    daddu     $4, $5, $0;
    addiu      $5, $5, 0x10;
  L00134C28:
    lq         $2, 0x0($5);
    pnor       $3, $0, $2;
    psubb      $2, $2, $8;
    pand       $2, $2, $3;
    pand       $4, $2, $9;
    pcpyud     $3, $4, $6;
    or         $3, $3, $4;
    beql       $3, $0, L00134C28;
    addiu     $5, $5, 0x10;
    b          L00134CC4;
    daddu     $4, $5, $0;
  L00134C54:
    ld         $3, 0x0($5);
    lui        $4, (0x80808080 >> 16);
    ori        $4, $4, (0x80808080 & 0xFFFF);
    dsll       $4, $4, 16;
    ori        $4, $4, 0x8080;
    dsll       $4, $4, 16;
    ori        $4, $4, 0x8080;
    dsubu      $2, $3, $2;
    nor        $3, $0, $3;
    and        $2, $2, $3;
    and        $2, $2, $4;
    bnel       $2, $0, L00134CC4;
    daddu     $4, $5, $0;
    lui        $6, (0x1010101 >> 16);
    ori        $6, $6, (0x1010101 & 0xFFFF);
    dsll       $6, $6, 16;
    ori        $6, $6, 0x101;
    dsll       $6, $6, 16;
    ori        $6, $6, 0x101;
    addiu      $5, $5, 0x8;
  L00134CA4:
    ld         $2, 0x0($5);
    nor        $3, $0, $2;
    dsubu      $2, $2, $6;
    and        $2, $2, $3;
    and        $2, $2, $4;
    beql       $2, $0, L00134CA4;
    addiu     $5, $5, 0x8;
    daddu      $4, $5, $0;
  L00134CC4:
    lb         $2, 0x0($4);
    nop;
    nop;
    nop;
    nop;
    bnel       $2, $0, L00134CC4;
    addiu     $4, $4, 0x1;
    jr         $31;
    subu      $2, $4, $7;
}

