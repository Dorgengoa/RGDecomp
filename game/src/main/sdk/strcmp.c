#include "types.h"

asm void strcmp(void)
{
    .set noreorder;
    or         $8, $4, $5;
    andi       $2, $8, 0x7;
    bnel       $2, $0, L00134A80;
    lb        $2, 0x0($4);
    andi       $9, $8, 0xF;
    lui        $7, (0x1010101 >> 16);
    ori        $7, $7, (0x1010101 & 0xFFFF);
    dsll       $7, $7, 16;
    ori        $7, $7, 0x101;
    dsll       $7, $7, 16;
    ori        $7, $7, 0x101;
    lui        $6, (0x80808080 >> 16);
    ori        $6, $6, (0x80808080 & 0xFFFF);
    dsll       $6, $6, 16;
    ori        $6, $6, 0x8080;
    dsll       $6, $6, 16;
    ori        $6, $6, 0x8080;
    bnez       $9, L00134A14;
    ld        $2, 0x0($5);
    lq         $3, 0x0($4);
    pcpyld     $8, $7, $7;
    lq         $2, 0x0($5);
    pcpyld     $10, $6, $6;
    psubw      $7, $2, $3;
    pcpyud     $6, $7, $4;
    or         $3, $6, $7;
    bnel       $3, $0, L00134A80;
    lb        $2, 0x0($4);
    lq         $2, 0x0($4);
    pnor       $3, $0, $2;
  L001349C8:
    psubb      $2, $2, $8;
    pand       $2, $2, $3;
    pand       $2, $2, $10;
    pcpyud     $3, $2, $4;
    or         $6, $3, $2;
    beqz       $6, L001349EC;
    addiu     $4, $4, 0x10;
    jr         $31;
    daddu     $2, $0, $0;
  L001349EC:
    addiu      $5, $5, 0x10;
    lq         $2, 0x0($4);
    lq         $3, 0x0($5);
    psubw      $7, $2, $3;
    pcpyud     $6, $7, $4;
    or         $9, $6, $7;
    beql       $9, $0, L001349C8;
    pnor      $3, $0, $2;
    b          L00134A80;
    lb        $2, 0x0($4);
  L00134A14:
    ld         $3, 0x0($4);
    bnel       $3, $2, L00134A80;
    lb        $2, 0x0($4);
    ld         $2, 0x0($4);
    nor        $8, $0, $2;
  L00134A28:
    dsubu      $2, $2, $7;
    and        $2, $2, $8;
    and        $2, $2, $6;
    beqz       $2, L00134A44;
    addiu     $4, $4, 0x8;
    jr         $31;
    daddu     $2, $0, $0;
  L00134A44:
    addiu      $5, $5, 0x8;
    ld         $2, 0x0($4);
    ld         $3, 0x0($5);
    beql       $3, $2, L00134A28;
    nor       $8, $0, $2;
    b          L00134A80;
    lb        $2, 0x0($4);
  L00134A60:
    sll        $2, $3, 24;
    lb         $3, 0x0($5);
    sra        $2, $2, 24;
    bnel       $2, $3, L00134A88;
    lbu       $3, 0x0($4);
    addiu      $4, $4, 0x1;
    addiu      $5, $5, 0x1;
    lb         $2, 0x0($4);
  L00134A80:
    bnez       $2, L00134A60;
    lbu       $3, 0x0($4);
  L00134A88:
    lbu        $2, 0x0($5);
    jr         $31;
    subu      $2, $3, $2;
}

