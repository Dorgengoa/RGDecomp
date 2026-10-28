#include "types.h"

extern void dpmul(void);
extern void dpadd(void);
extern void Copysign_128230(void);

asm void ScalbnDouble_128698(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $6, $4, $0;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $17, 0x8($29);
    daddu      $2, $6, $0;
    dsll32     $5, $2, 0;
    dsra32     $5, $5, 0;
    dsra32     $7, $2, 0;
    lui        $17, (0x7FF00000 >> 16);
    and        $2, $7, $17;
    sra        $3, $2, 20;
    bnez       $3, L00128740;
    sd        $31, 0x10($29);
    lui        $3, (0x7FFFFFFF >> 16);
    daddu      $2, $6, $0;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    and        $3, $7, $3;
    or         $3, $5, $3;
    beql       $3, $0, L0012886C;
    ld        $16, 0x0($29);
    ori        $5, $0, 0x86A0;
    dsll32     $5, $5, 15;
    jal        dpmul;
    nop;
    daddu      $6, $2, $0;
    dsra32     $7, $2, 0;
    and        $3, $7, $17;
    lui        $2, (0xFFFF3CB0 >> 16);
    ori        $2, $2, (0xFFFF3CB0 & 0xFFFF);
    sra        $3, $3, 20;
    slt        $2, $16, $2;
    beqz       $2, L00128740;
    addiu     $3, $3, -0x36;
    lui        $2, 0x45;
    daddu      $4, $6, $0;
    ld         $5, 0x7970($2);
    jal        dpmul;
    nop;
    b          L0012886C;
    ld        $16, 0x0($29);
    nop;
  L00128740:
    addiu      $2, $0, 0x7FF;
    bne        $3, $2, L00128768;
    addu      $3, $3, $16;
    daddu      $4, $6, $0;
    daddu      $5, $4, $0;
    jal        dpadd;
    nop;
    b          L0012886C;
    ld        $16, 0x0($29);
    nop;
  L00128768:
    slti       $2, $3, 0x7FF;
    bnez       $2, L00128788;
    lui       $2, 0x45;
    daddu      $5, $6, $0;
    ld         $16, 0x7978($2);
    b          L00128800;
    nop;
    nop;
  L00128788:
    blezl      $3, L001287C8;
    slti      $2, $3, -0x35;
    lui        $2, (0x800FFFFF >> 16);
    sll        $5, $3, 20;
    ori        $2, $2, (0x800FFFFF & 0xFFFF);
    lui        $4, (0xFFFF0000 >> 16);
    dsrl32     $4, $4, 0;
    and        $2, $7, $2;
    daddu      $3, $6, $0;
    or         $2, $2, $5;
    and        $3, $3, $4;
    dsll32     $2, $2, 0;
    or         $6, $3, $2;
    daddu      $2, $6, $0;
    b          L0012886C;
    ld        $16, 0x0($29);
  L001287C8:
    beql       $2, $0, L00128828;
    addiu     $3, $3, 0x36;
    ori        $2, $0, 0xC350;
    slt        $2, $2, $16;
    beqz       $2, L001287F8;
    lui       $2, 0x45;
    lui        $2, 0x45;
    daddu      $5, $6, $0;
    ld         $16, 0x7978($2);
    b          L00128800;
    nop;
    nop;
  L001287F8:
    daddu      $5, $6, $0;
    ld         $16, 0x7970($2);
  L00128800:
    daddu      $4, $16, $0;
    jal        Copysign_128230;
    nop;
    daddu      $5, $16, $0;
    daddu      $4, $2, $0;
    jal        dpmul;
    nop;
    b          L0012886C;
    ld        $16, 0x0($29);
    nop;
  L00128828:
    daddu      $4, $6, $0;
    lui        $2, (0x800FFFFF >> 16);
    ori        $2, $2, (0x800FFFFF & 0xFFFF);
    sll        $5, $3, 20;
    and        $2, $7, $2;
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    or         $2, $2, $5;
    and        $4, $4, $3;
    dsll32     $2, $2, 0;
    or         $6, $4, $2;
    daddu      $4, $6, $0;
    ori        $5, $0, 0xF240;
    dsll32     $5, $5, 14;
    jal        dpmul;
    nop;
    ld         $16, 0x0($29);
  L0012886C:
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
