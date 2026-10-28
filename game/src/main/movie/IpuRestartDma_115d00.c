#include "types.h"

extern void DmaIpuFromSetChcr_115b28(void);
extern void DmaIpuToSetChcr_115ba0(void);

asm void IpuRestartDma_115d00(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x40($29);
    daddu      $16, $4, $0;
    lw         $2, 0x1C($16);
    lw         $4, 0x8($16);
    srl        $3, $2, 8;
    andi       $19, $2, 0x7F;
    srl        $2, $2, 16;
    andi       $3, $3, 0xF;
    andi       $2, $2, 0x3;
    lw         $5, 0x0($16);
    addu       $2, $2, $3;
    lw         $6, 0x10($16);
    addu       $18, $4, $2;
    sll        $2, $2, 4;
    beqz       $6, L00115D84;
    subu      $17, $5, $2;
    lw         $2, 0x14($16);
    beqz       $2, L00115D84;
    lui       $2, (0x1000B010 >> 16);
    lui        $4, (0x1000B020 >> 16);
    ori        $2, $2, (0x1000B010 & 0xFFFF);
    ori        $4, $4, (0x1000B020 & 0xFFFF);
    sw         $6, 0x0($2);
    lw         $3, 0x14($16);
    sw         $3, 0x0($4);
    lw         $4, 0x18($16);
    jal        DmaIpuFromSetChcr_115b28;
    ori       $4, $4, 0x100;
  L00115D84:
    lui        $3, (0x10002010 >> 16);
    ori        $3, $3, (0x10002010 & 0xFFFF);
    nop;
  L00115D90:
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    nop;
    bltz       $2, L00115D90;
    nop;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x10002010 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    ori        $3, $3, (0x10002010 & 0xFFFF);
    sw         $19, 0x0($2);
  L00115DC0:
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    nop;
    bltz       $2, L00115DC0;
    nop;
    beqz       $17, L00115E38;
    ld        $31, 0x40($29);
    beqz       $18, L00115E3C;
    ld        $19, 0x30($29);
    lui        $2, (0x1000B410 >> 16);
    lui        $4, (0x1000B430 >> 16);
    ori        $2, $2, (0x1000B410 & 0xFFFF);
    ori        $4, $4, (0x1000B430 & 0xFFFF);
    sw         $17, 0x0($2);
    lui        $3, (0x1000B420 >> 16);
    ori        $3, $3, (0x1000B420 & 0xFFFF);
    ld         $31, 0x40($29);
    lw         $2, 0x4($16);
    ld         $19, 0x30($29);
    sw         $2, 0x0($4);
    sw         $18, 0x0($3);
    ld         $18, 0x20($29);
    lw         $4, 0xC($16);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    ori        $4, $4, 0x100;
    j          DmaIpuToSetChcr_115ba0;
    addiu     $29, $29, 0x50;
  L00115E38:
    ld         $19, 0x30($29);
  L00115E3C:
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
