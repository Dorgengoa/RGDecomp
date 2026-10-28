#include "types.h"

extern void sceGsGetGParam_1082a0(void);
extern void VSync_116a30(void);
extern void VSync2_116ac0(void);

asm void sceGsSyncV(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        sceGsGetGParam_1082a0;
    nop;
    daddu      $16, $2, $0;
    lw         $2, 0x8($16);
    bnez       $2, L00108FF8;
    nop;
    jal        VSync_116a30;
    nop;
    lh         $3, 0x0($16);
    addiu      $2, $0, 0x1;
    bne        $3, $2, L00109020;
    ld        $31, 0x10($29);
    lui        $3, (0x12001000 >> 16);
    ori        $3, $3, (0x12001000 & 0xFFFF);
    ld         $2, 0x0($3);
    dsrl       $2, $2, 13;
    andi       $2, $2, 0x1;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    b          L00109024;
    ld        $16, 0x0($29);
  L00108FF8:
    jal        VSync2_116ac0;
    nop;
    dsra       $2, $2, 13;
    lh         $3, 0x0($16);
    andi       $4, $2, 0x1;
    addiu      $2, $0, 0x1;
    bne        $3, $2, L00109020;
    ld        $31, 0x10($29);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
  L00109020:
    ld         $16, 0x0($29);
  L00109024:
    jr         $31;
    addiu     $29, $29, 0x20;
}

