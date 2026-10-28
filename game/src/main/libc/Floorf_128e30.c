#include "types.h"

asm void Floorf_128e30(void)
{
    .set noreorder;
    mfc1       $3, $f12;
    daddu      $4, $3, $0;
    lui        $2, (0x7FFFFFFF >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    and        $6, $4, $2;
    srl        $3, $6, 23;
    addiu      $5, $3, -0x7F;
    slti       $2, $5, 0x17;
    beqz       $2, L00128F00;
    mov.s     $f0, $f12;
    bgezl      $5, L00128EA8;
    lui       $2, (0x7FFFFF >> 16);
    lui        $1, (0x7149F2C9 >> 16);
    ori        $1, $1, (0x7149F2C9 & 0xFFFF);
    mtc1       $1, $f0;
    mtc1       $0, $f1;
    add.s      $f0, $f12, $f0;
    c.lt.s     $f1, $f0;
    bc1f       L00128EF8;
    nop;
    bltz       $4, L00128E90;
    lui       $2, (0x7FFFFF >> 16);
    b          L00128EF8;
    daddu     $4, $0, $0;
  L00128E90:
    ori        $2, $2, (0x7FFFFF & 0xFFFF);
    sltu       $2, $2, $6;
    bnel       $2, $0, L00128EF8;
    lui       $4, (0xBF800000 >> 16);
    b          L00128EF8;
    nop;
  L00128EA8:
    ori        $2, $2, (0x7FFFFF & 0xFFFF);
    srav       $6, $2, $5;
    and        $3, $4, $6;
    beqz       $3, L00128F00;
    mov.s     $f0, $f12;
    lui        $1, (0x7149F2C9 >> 16);
    ori        $1, $1, (0x7149F2C9 & 0xFFFF);
    mtc1       $1, $f0;
    mtc1       $0, $f1;
    add.s      $f0, $f12, $f0;
    c.lt.s     $f1, $f0;
    bc1f       L00128EF8;
    nop;
    bgez       $4, L00128EF4;
    nor       $2, $0, $6;
    lui        $2, (0x800000 >> 16);
    srav       $2, $2, $5;
    addu       $4, $4, $2;
    nor        $2, $0, $6;
  L00128EF4:
    and        $4, $4, $2;
  L00128EF8:
    mtc1       $4, $f12;
    mtc1       $4, $f0;
  L00128F00:
    jr         $31;
    nop;
}
