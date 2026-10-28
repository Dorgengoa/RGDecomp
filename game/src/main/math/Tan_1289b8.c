#include "types.h"

extern void KernelTan_126ab8(void);
extern void dpsub(void);
extern void IeeeRemPio2_123b78(void);

asm void Tan_1289b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $8, $4, $0;
    sd         $31, 0x10($29);
    daddu      $6, $8, $0;
    dsra32     $6, $6, 0;
    lui        $3, (0x7FFFFFFF >> 16);
    daddu      $5, $0, $0;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    lui        $7, (0x3FE921FB >> 16);
    and        $6, $6, $3;
    lui        $2, (0x7FEFFFFF >> 16);
    ori        $7, $7, (0x3FE921FB & 0xFFFF);
    ori        $2, $2, (0x7FEFFFFF & 0xFFFF);
    slt        $7, $7, $6;
    slt        $2, $2, $6;
    bnez       $7, L00128A10;
    addiu     $6, $0, 0x1;
    jal        KernelTan_126ab8;
    nop;
    b          L00128A58;
    ld        $31, 0x10($29);
    nop;
  L00128A10:
    beqz       $2, L00128A30;
    nop;
    daddu      $5, $8, $0;
    jal        dpsub;
    nop;
    b          L00128A58;
    ld        $31, 0x10($29);
    nop;
  L00128A30:
    jal        IeeeRemPio2_123b78;
    daddu     $5, $29, $0;
    addiu      $6, $0, 0x1;
    andi       $2, $2, 0x1;
    ld         $4, 0x0($29);
    sll        $2, $2, 1;
    ld         $5, 0x8($29);
    jal        KernelTan_126ab8;
    subu      $6, $6, $2;
    ld         $31, 0x10($29);
  L00128A58:
    jr         $31;
    addiu     $29, $29, 0x20;
}
