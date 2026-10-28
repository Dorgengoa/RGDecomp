#include "types.h"

extern void Copysignf_128cf0(void);

asm void Scalbnf_128f08(void)
{
    .set noreorder;
    mfc1       $6, $f12;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    swc1       $f20, 0x8($29);
    lui        $2, (0x7FFFFFFF >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    lui        $3, (0x7FFFFF >> 16);
    and        $2, $6, $2;
    ori        $3, $3, (0x7FFFFF & 0xFFFF);
    srl        $5, $2, 23;
    sltu       $3, $3, $2;
    mov.s      $f0, $f12;
    beqz       $3, L00128FC0;
    addu      $5, $5, $4;
    slti       $2, $5, 0x100;
    bnez       $2, L00128F60;
    mov.s     $f13, $f12;
    lui        $1, (0x7149F2C9 >> 16);
    ori        $1, $1, (0x7149F2C9 & 0xFFFF);
    mtc1       $1, $f20;
    b          L00128FB4;
    nop;
  L00128F60:
    blez       $5, L00128F88;
    ori       $2, $0, 0xC350;
    lui        $2, (0x807FFFFF >> 16);
    sll        $3, $5, 23;
    ori        $2, $2, (0x807FFFFF & 0xFFFF);
    and        $2, $6, $2;
    or         $2, $2, $3;
    mtc1       $2, $f12;
    b          L00128FC0;
    mov.s     $f0, $f12;
  L00128F88:
    slt        $2, $2, $4;
    beqz       $2, L00128FA8;
    mov.s     $f13, $f12;
    lui        $1, (0x7149F2C9 >> 16);
    ori        $1, $1, (0x7149F2C9 & 0xFFFF);
    mtc1       $1, $f20;
    b          L00128FB4;
    nop;
  L00128FA8:
    lui        $1, (0xDA2425F >> 16);
    ori        $1, $1, (0xDA2425F & 0xFFFF);
    mtc1       $1, $f20;
  L00128FB4:
    jal        Copysignf_128cf0;
    mov.s     $f12, $f20;
    mul.s      $f0, $f0, $f20;
  L00128FC0:
    ld         $31, 0x0($29);
    lwc1       $f20, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
