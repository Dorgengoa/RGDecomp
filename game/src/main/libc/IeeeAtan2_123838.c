#include "types.h"

extern void dpadd(void);
extern void AtanDouble_127d68(void);
extern void dpdiv(void);
extern void FabsDouble_1283a0(void);
extern void dpsub(void);

asm void IeeeAtan2_123838(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $12, $4, $0;
    sd         $16, 0x0($29);
    daddu      $3, $5, $0;
    dsll32     $7, $3, 0;
    dsra32     $7, $7, 0;
    dsra32     $11, $3, 0;
    lui        $2, (0x7FFFFFFF >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    and        $9, $11, $2;
    daddu      $3, $12, $0;
    dsll32     $6, $3, 0;
    dsra32     $6, $6, 0;
    dsra32     $10, $3, 0;
    and        $8, $10, $2;
    lui        $3, (0x7FF00000 >> 16);
    negu       $2, $7;
    or         $2, $7, $2;
    srl        $2, $2, 31;
    or         $2, $9, $2;
    sltu       $2, $3, $2;
    bnez       $2, L001238B0;
    sd        $31, 0x8($29);
    negu       $2, $6;
    or         $2, $6, $2;
    srl        $2, $2, 31;
    or         $2, $8, $2;
    sltu       $2, $3, $2;
    beql       $2, $0, L001238C8;
    lui       $2, (0xC0100000 >> 16);
  L001238B0:
    daddu      $4, $5, $0;
    daddu      $5, $12, $0;
    jal        dpadd;
    nop;
    b          L00123B68;
    ld        $16, 0x0($29);
  L001238C8:
    addu       $2, $11, $2;
    or         $2, $2, $7;
    bnel       $2, $0, L001238E8;
    sra       $2, $11, 30;
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    j          AtanDouble_127d68;
    addiu     $29, $29, 0x10;
  L001238E8:
    srl        $3, $10, 31;
    andi       $2, $2, 0x2;
    or         $4, $8, $6;
    bnez       $4, L00123940;
    or        $16, $3, $2;
    addiu      $3, $0, 0x2;
    lui        $1, 0x45;
    ld         $2, 0x6F08($1);
    beql       $16, $3, L00123B68;
    ld        $16, 0x0($29);
    slti       $2, $16, 0x3;
    beql       $2, $0, L00123930;
    addiu     $3, $0, 0x3;
    bltzl      $16, L00123944;
    or        $2, $9, $7;
    daddu      $2, $12, $0;
    b          L00123B68;
    ld        $16, 0x0($29);
  L00123930:
    lui        $1, 0x45;
    ld         $2, 0x6F10($1);
    beql       $16, $3, L00123B68;
    ld        $16, 0x0($29);
  L00123940:
    or         $2, $9, $7;
  L00123944:
    beqz       $2, L00123A30;
    lui       $2, (0x7FF00000 >> 16);
    bne        $9, $2, L00123A28;
    nop;
    bne        $8, $9, L001239C8;
    addiu     $2, $0, 0x1;
    addiu      $3, $0, 0x1;
    lui        $1, 0x45;
    ld         $2, 0x6F18($1);
    beql       $16, $3, L00123B68;
    ld        $16, 0x0($29);
    slti       $2, $16, 0x2;
    beql       $2, $0, L00123998;
    addiu     $3, $0, 0x2;
    lui        $1, 0x45;
    ld         $2, 0x6F20($1);
    beql       $16, $0, L00123B68;
    ld        $16, 0x0($29);
    b          L00123A28;
    lui       $2, (0x7FF00000 >> 16);
    nop;
  L00123998:
    lui        $1, 0x45;
    ld         $2, 0x6F28($1);
    beql       $16, $3, L00123B68;
    ld        $16, 0x0($29);
    addiu      $2, $0, 0x3;
    bnel       $16, $2, L00123A28;
    lui       $2, (0x7FF00000 >> 16);
    lui        $1, 0x45;
    ld         $2, 0x6F30($1);
    b          L00123B68;
    ld        $16, 0x0($29);
    nop;
  L001239C8:
    beq        $16, $2, L00123A18;
    lui       $3, 0x45;
    slti       $2, $16, 0x2;
    beqz       $2, L001239F0;
    addiu     $3, $0, 0x2;
    daddu      $2, $0, $0;
    beql       $16, $0, L00123B68;
    ld        $16, 0x0($29);
    b          L00123A28;
    lui       $2, (0x7FF00000 >> 16);
  L001239F0:
    lui        $1, 0x45;
    ld         $2, 0x6F38($1);
    beq        $16, $3, L00123B64;
    addiu     $3, $0, 0x3;
    lui        $1, 0x45;
    ld         $2, 0x6F40($1);
    beql       $16, $3, L00123B68;
    ld        $16, 0x0($29);
    b          L00123A28;
    lui       $2, (0x7FF00000 >> 16);
  L00123A18:
    ld         $2, 0x6F00($3);
    b          L00123B68;
    ld        $16, 0x0($29);
    nop;
  L00123A28:
    bne        $8, $2, L00123A50;
    subu      $3, $8, $9;
  L00123A30:
    lui        $1, 0x45;
    ld         $2, 0x6F48($1);
    bltz       $10, L00123B64;
    ld        $16, 0x0($29);
    lui        $1, 0x45;
    ld         $2, 0x6F50($1);
    b          L00123B6C;
    ld        $31, 0x8($29);
  L00123A50:
    lui        $1, 0x45;
    ld         $4, 0x6F58($1);
    sra        $3, $3, 20;
    slti       $2, $3, 0x3D;
    beqz       $2, L00123AA8;
    addiu     $2, $0, 0x1;
    bgez       $11, L00123A7C;
    slti      $2, $3, -0x3C;
    daddu      $4, $0, $0;
    bnez       $2, L00123AA8;
    addiu     $2, $0, 0x1;
  L00123A7C:
    daddu      $4, $12, $0;
    jal        dpdiv;
    nop;
    daddu      $4, $2, $0;
    jal        FabsDouble_1283a0;
    nop;
    daddu      $4, $2, $0;
    jal        AtanDouble_127d68;
    nop;
    daddu      $4, $2, $0;
    addiu      $2, $0, 0x1;
  L00123AA8:
    beq        $16, $2, L00123AE0;
    lui       $3, (0x80000000 >> 16);
    slti       $2, $16, 0x2;
    beqz       $2, L00123AD0;
    addiu     $2, $0, 0x2;
    daddu      $2, $4, $0;
    beqz       $16, L00123B68;
    ld        $16, 0x0($29);
    b          L00123B40;
    nop;
  L00123AD0:
    beq        $16, $2, L00123B10;
    nop;
    b          L00123B40;
    nop;
  L00123AE0:
    daddu      $2, $4, $0;
    dsra32     $2, $2, 0;
    lui        $5, (0xFFFF0000 >> 16);
    dsrl32     $5, $5, 0;
    xor        $2, $2, $3;
    and        $4, $4, $5;
    dsll32     $2, $2, 0;
    or         $4, $4, $2;
    daddu      $2, $4, $0;
    b          L00123B68;
    ld        $16, 0x0($29);
    nop;
  L00123B10:
    lui        $1, 0x45;
    ld         $5, 0x6F60($1);
    jal        dpsub;
    nop;
    lui        $1, 0x45;
    ld         $4, 0x6F68($1);
    daddu      $5, $2, $0;
    jal        dpsub;
    nop;
    b          L00123B68;
    ld        $16, 0x0($29);
    nop;
  L00123B40:
    lui        $1, 0x45;
    ld         $5, 0x6F70($1);
    jal        dpsub;
    nop;
    lui        $1, 0x45;
    ld         $5, 0x6F78($1);
    daddu      $4, $2, $0;
    jal        dpsub;
    nop;
  L00123B64:
    ld         $16, 0x0($29);
  L00123B68:
    ld         $31, 0x8($29);
  L00123B6C:
    jr         $31;
    addiu     $29, $29, 0x10;
}
