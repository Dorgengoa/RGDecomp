#include "types.h"

extern void B2d_1328a8(void);
extern void dpdiv(void);

asm void Ratio_132bc8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x18($29);
    daddu      $17, $5, $0;
    daddu      $5, $29, $0;
    sd         $16, 0x10($29);
    sd         $18, 0x20($29);
    sd         $31, 0x28($29);
    jal        B2d_1328a8;
    daddu     $16, $4, $0;
    addiu      $5, $29, 0x4;
    daddu      $4, $17, $0;
    jal        B2d_1328a8;
    daddu     $18, $2, $0;
    lw         $3, 0x10($16);
    daddu      $8, $2, $0;
    lw         $6, 0x10($17);
    dsra32     $5, $18, 0;
    lw         $4, 0x4($29);
    dsra32     $7, $8, 0;
    lw         $2, 0x0($29);
    subu       $3, $3, $6;
    sll        $3, $3, 5;
    subu       $2, $2, $4;
    addu       $2, $2, $3;
    sll        $4, $2, 20;
    daddu      $3, $4, $0;
    addu       $5, $5, $4;
    subu       $3, $7, $3;
    blez       $2, L00132C58;
    dsll32    $5, $5, 0;
    lui        $2, (0xFFFF0000 >> 16);
    dsrl32     $2, $2, 0;
    and        $18, $18, $2;
    b          L00132C6C;
    or        $18, $18, $5;
    nop;
  L00132C58:
    lui        $2, (0xFFFF0000 >> 16);
    dsrl32     $2, $2, 0;
    dsll32     $3, $3, 0;
    and        $8, $8, $2;
    or         $8, $8, $3;
  L00132C6C:
    daddu      $4, $18, $0;
    daddu      $5, $8, $0;
    jal        dpdiv;
    nop;
    ld         $16, 0x10($29);
    ld         $17, 0x18($29);
    ld         $18, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
