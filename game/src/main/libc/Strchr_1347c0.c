#include "types.h"

asm void Strchr_1347c0(void)
{
    .set noreorder;
    andi       $2, $4, 0x7;
    bnez       $2, L00134930;
    andi      $5, $5, 0xFF;
    dsll       $3, $5, 8;
    lui        $6, (0x1010101 >> 16);
    ori        $6, $6, (0x1010101 & 0xFFFF);
    dsll       $6, $6, 16;
    ori        $6, $6, 0x101;
    dsll       $6, $6, 16;
    ori        $6, $6, 0x101;
    daddu      $10, $3, $5;
    andi       $3, $4, 0xF;
    dsll       $2, $10, 16;
    lui        $8, (0x80808080 >> 16);
    ori        $8, $8, (0x80808080 & 0xFFFF);
    dsll       $8, $8, 16;
    ori        $8, $8, 0x8080;
    dsll       $8, $8, 16;
    ori        $8, $8, 0x8080;
    daddu      $2, $2, $10;
    dsll32     $10, $2, 0;
    bnez       $3, L001348A8;
    daddu     $7, $2, $10;
  L0013481C:
    lq         $9, 0x0($4);
    pcpyld     $10, $6, $6;
    pnor       $3, $0, $9;
    psubb      $2, $9, $10;
    pcpyld     $6, $8, $8;
    pand       $2, $2, $3;
    pcpyld     $8, $7, $7;
    pand       $2, $2, $6;
    pcpyud     $3, $2, $7;
    or         $3, $2, $3;
    bnel       $3, $0, L00134934;
    lbu       $2, 0x0($4);
    pxor       $2, $9, $8;
    psubb      $3, $2, $10;
    pnor       $2, $0, $2;
    lui        $8, (0x80808080 >> 16);
    ori        $8, $8, (0x80808080 & 0xFFFF);
    dsll       $8, $8, 16;
    ori        $8, $8, 0x8080;
    dsll       $8, $8, 16;
    ori        $8, $8, 0x8080;
    pand       $3, $3, $2;
    pand       $3, $3, $6;
    lui        $6, (0x1010101 >> 16);
    ori        $6, $6, (0x1010101 & 0xFFFF);
    dsll       $6, $6, 16;
    ori        $6, $6, 0x101;
    dsll       $6, $6, 16;
    ori        $6, $6, 0x101;
    pcpyud     $2, $3, $5;
    or         $3, $2, $3;
    beql       $3, $0, L0013481C;
    addiu     $4, $4, 0x10;
    b          L00134934;
    lbu       $2, 0x0($4);
  L001348A8:
    ld         $9, 0x0($4);
    nor        $3, $0, $9;
    dsubu      $2, $9, $6;
    and        $2, $2, $3;
    and        $2, $2, $8;
    bnel       $2, $0, L00134934;
    lbu       $2, 0x0($4);
    xor        $2, $9, $7;
    dsubu      $3, $2, $6;
    nor        $2, $0, $2;
    and        $3, $3, $2;
    and        $3, $3, $8;
    bnel       $3, $0, L00134934;
    lbu       $2, 0x0($4);
    daddu      $9, $6, $0;
    addiu      $4, $4, 0x8;
  L001348E8:
    ld         $6, 0x0($4);
    dsubu      $2, $6, $9;
    nor        $3, $0, $6;
    and        $2, $2, $3;
    and        $2, $2, $8;
    bnez       $2, L00134930;
    xor       $2, $6, $7;
    nor        $3, $0, $2;
    dsubu      $2, $2, $9;
    and        $2, $2, $3;
    and        $2, $2, $8;
    beql       $2, $0, L001348E8;
    addiu     $4, $4, 0x8;
    b          L00134934;
    lbu       $2, 0x0($4);
  L00134924:
    beql       $2, $5, L00134940;
    lbu       $3, 0x0($4);
    addiu      $4, $4, 0x1;
  L00134930:
    lbu        $2, 0x0($4);
  L00134934:
    bnez       $2, L00134924;
    nop;
    lbu        $3, 0x0($4);
  L00134940:
    daddu      $2, $0, $0;
    xor        $3, $3, $5;
    jr         $31;
    movz      $2, $4, $3;
}

