#include "types.h"

extern void Atanf_128a60(void);
extern void Fabsf_128e08(void);

asm void IeeeAtan2f_124c18(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    mov.s      $f1, $f12;
    sd         $16, 0x10($29);
    sd         $31, 0x18($29);
    mfc1       $6, $f13;
    lui        $2, (0x7FFFFFFF >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    and        $8, $6, $2;
    mfc1       $5, $f1;
    lui        $3, (0x3F800000 >> 16);
    bne        $6, $3, L00124C58;
    and       $7, $5, $2;
    ld         $16, 0x10($29);
    ld         $31, 0x18($29);
    j          Atanf_128a60;
    addiu     $29, $29, 0x20;
  L00124C58:
    lui        $2, (0x7FFFFF >> 16);
    sra        $4, $6, 30;
    ori        $2, $2, (0x7FFFFF & 0xFFFF);
    andi       $4, $4, 0x2;
    srl        $3, $5, 31;
    slt        $2, $2, $7;
    bnez       $2, L00124CBC;
    or        $16, $3, $4;
    addiu      $2, $0, 0x2;
    lui        $1, (0x40490FDA >> 16);
    ori        $1, $1, (0x40490FDA & 0xFFFF);
    mtc1       $1, $f0;
    beq        $16, $2, L00124DE8;
    slti      $2, $16, 0x3;
    beql       $2, $0, L00124CA8;
    addiu     $2, $0, 0x3;
    bltz       $16, L00124CC0;
    lui       $2, (0x7FFFFF >> 16);
    b          L00124DE8;
    mov.s     $f0, $f1;
  L00124CA8:
    lui        $1, (0xC0490FDA >> 16);
    ori        $1, $1, (0xC0490FDA & 0xFFFF);
    mtc1       $1, $f0;
    beql       $16, $2, L00124DEC;
    ld        $16, 0x10($29);
  L00124CBC:
    lui        $2, (0x7FFFFF >> 16);
  L00124CC0:
    ori        $2, $2, (0x7FFFFF & 0xFFFF);
    slt        $2, $2, $8;
    bnez       $2, L00124CF8;
    subu      $3, $7, $8;
    lui        $1, (0xBFC90FDA >> 16);
    ori        $1, $1, (0xBFC90FDA & 0xFFFF);
    mtc1       $1, $f0;
    bltz       $5, L00124DE8;
    ld        $16, 0x10($29);
    lui        $1, (0x3FC90FDA >> 16);
    ori        $1, $1, (0x3FC90FDA & 0xFFFF);
    mtc1       $1, $f0;
    b          L00124DF0;
    ld        $31, 0x18($29);
  L00124CF8:
    lui        $1, (0x3FC90FDA >> 16);
    ori        $1, $1, (0x3FC90FDA & 0xFFFF);
    mtc1       $1, $f2;
    sra        $3, $3, 23;
    slti       $2, $3, 0x3D;
    beqz       $2, L00124D4C;
    addiu     $2, $0, 0x1;
    bgez       $6, L00124D28;
    slti      $2, $3, -0x3C;
    mtc1       $0, $f2;
    bnez       $2, L00124D4C;
    addiu     $2, $0, 0x1;
  L00124D28:
    nop;
    nop;
    div.s      $f12, $f1, $f13;
    jal        Fabsf_128e08;
    nop;
    jal        Atanf_128a60;
    mov.s     $f12, $f0;
    mov.s      $f2, $f0;
    addiu      $2, $0, 0x1;
  L00124D4C:
    beq        $16, $2, L00124D80;
    slti      $2, $16, 0x2;
    beql       $2, $0, L00124D70;
    addiu     $2, $0, 0x2;
    beqz       $16, L00124DE8;
    mov.s     $f0, $f2;
    b          L00124DC8;
    nop;
    nop;
  L00124D70:
    beq        $16, $2, L00124DA0;
    nop;
    b          L00124DC8;
    nop;
  L00124D80:
    swc1       $f2, 0x0($29);
    lui        $2, (0x80000000 >> 16);
    lw         $3, 0x0($29);
    xor        $3, $3, $2;
    mtc1       $3, $f2;
    b          L00124DE8;
    mov.s     $f0, $f2;
    nop;
  L00124DA0:
    lui        $1, (0x34222168 >> 16);
    ori        $1, $1, (0x34222168 & 0xFFFF);
    mtc1       $1, $f0;
    lui        $1, (0x40490FDA >> 16);
    ori        $1, $1, (0x40490FDA & 0xFFFF);
    mtc1       $1, $f1;
    sub.s      $f0, $f2, $f0;
    b          L00124DE8;
    sub.s     $f0, $f1, $f0;
    nop;
  L00124DC8:
    lui        $1, (0x34222168 >> 16);
    ori        $1, $1, (0x34222168 & 0xFFFF);
    mtc1       $1, $f0;
    lui        $1, (0x40490FDA >> 16);
    ori        $1, $1, (0x40490FDA & 0xFFFF);
    mtc1       $1, $f1;
    sub.s      $f0, $f2, $f0;
    sub.s      $f0, $f0, $f1;
  L00124DE8:
    ld         $16, 0x10($29);
  L00124DEC:
    ld         $31, 0x18($29);
  L00124DF0:
    jr         $31;
    addiu     $29, $29, 0x20;
}
