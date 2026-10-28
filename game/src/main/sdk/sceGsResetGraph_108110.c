#include "types.h"

extern void sceGsGetGParam_1082a0(void);
extern void GsPutIMR(void);
extern void DisableIntc_117080(void);
extern void RemoveIntcHandler(void);
extern void SetGsCrt(void);

asm void sceGsResetGraph_108110(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sll        $4, $4, 16;
    sd         $19, 0x30($29);
    sll        $5, $5, 16;
    sd         $18, 0x20($29);
    sll        $6, $6, 16;
    sd         $17, 0x10($29);
    sll        $7, $7, 16;
    sd         $31, 0x40($29);
    sra        $4, $4, 16;
    sd         $16, 0x0($29);
    sra        $17, $5, 16;
    sra        $18, $6, 16;
    addiu      $2, $0, 0x1;
    beq        $4, $2, L00108210;
    sra       $19, $7, 16;
    slti       $2, $4, 0x2;
    beql       $2, $0, L0010816C;
    addiu     $2, $0, 0x5;
    beqz       $4, L0010817C;
    ld        $31, 0x40($29);
    b          L0010828C;
    ld        $19, 0x30($29);
  L0010816C:
    beq        $4, $2, L00108228;
    ld        $31, 0x40($29);
    b          L0010828C;
    ld        $19, 0x30($29);
  L0010817C:
    jal        sceGsGetGParam_1082a0;
    nop;
    lui        $3, (0x12001000 >> 16);
    addiu      $4, $0, 0x200;
    ori        $3, $3, (0x12001000 & 0xFFFF);
    daddu      $16, $2, $0;
    sd         $4, 0x0($3);
    sh         $17, 0x0($16);
    ori        $4, $0, 0xFF00;
    ld         $2, 0x0($3);
    sh         $18, 0x2($16);
    dsrl       $2, $2, 16;
    andi       $2, $2, 0xFF;
    andi       $2, $2, 0xFFFF;
    jal        GsPutIMR;
    sh        $2, 0x6($16);
    sltu       $3, $0, $19;
    lw         $2, 0x8($16);
    beqz       $2, L001081E8;
    sh        $3, 0x4($16);
    jal        DisableIntc_117080;
    addiu     $4, $0, 0x2;
    lw         $5, 0xC($16);
    jal        RemoveIntcHandler;
    addiu     $4, $0, 0x2;
    sw         $0, 0xC($16);
    sw         $0, 0x8($16);
  L001081E8:
    andi       $4, $17, 0x1;
    andi       $5, $18, 0xFF;
    andi       $6, $19, 0x1;
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          SetGsCrt;
    addiu     $29, $29, 0x50;
  L00108210:
    lui        $2, (0x12001000 >> 16);
    addiu      $3, $0, 0x100;
    ori        $2, $2, (0x12001000 & 0xFFFF);
    sd         $3, 0x0($2);
    b          L00108288;
    ld        $31, 0x40($29);
  L00108228:
    jal        sceGsGetGParam_1082a0;
    nop;
    lui        $3, (0x12001000 >> 16);
    daddu      $16, $2, $0;
    ori        $3, $3, (0x12001000 & 0xFFFF);
    sltu       $6, $0, $19;
    ld         $2, 0x0($3);
    andi       $4, $17, 0x1;
    sh         $6, 0x4($16);
    andi       $5, $18, 0xFF;
    dsrl       $2, $2, 16;
    sh         $17, 0x0($16);
    andi       $2, $2, 0xFF;
    sh         $18, 0x2($16);
    andi       $2, $2, 0xFFFF;
    andi       $6, $19, 0x1;
    sh         $2, 0x6($16);
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          SetGsCrt;
    addiu     $29, $29, 0x50;
  L00108288:
    ld         $19, 0x30($29);
  L0010828C:
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

