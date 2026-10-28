#include "types.h"

extern void EhRegisterFragmentStubMaybe_1026b0(void);

asm void RunStaticCtors_100df0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    daddu      $19, $5, $0;
    sq         $17, 0x10($29);
    sltu       $1, $4, $19;
    sq         $16, 0x0($29);
    daddu      $18, $6, $0;
    daddu      $17, $7, $0;
    beqz       $1, L00100E40;
    daddu     $16, $4, $0;
  L00100E20:
    lw         $2, 0x0($16);
    jalr $31, $2;
    nop;
    addiu      $16, $16, 0x4;
    sltu       $2, $16, $19;
    nop;
    bnez       $2, L00100E20;
    nop;
  L00100E40:
    daddu      $4, $18, $0;
    jal        EhRegisterFragmentStubMaybe_1026b0;
    daddu     $5, $17, $0;
    ld         $31, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

