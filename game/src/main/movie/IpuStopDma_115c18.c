#include "types.h"

extern void DmaIpuToSetChcr_115ba0(void);
extern void DmaIpuFromSetChcr_115b28(void);

asm void IpuStopDma_115c18(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x10($29);
    jal        DmaIpuToSetChcr_115ba0;
    addiu     $4, $0, 0x1;
    lui        $2, (0x1000B410 >> 16);
    lui        $6, (0x1000B430 >> 16);
    ori        $2, $2, (0x1000B410 & 0xFFFF);
    ori        $6, $6, (0x1000B430 & 0xFFFF);
    lw         $3, 0x0($2);
    lui        $4, (0x1000B420 >> 16);
    ori        $4, $4, (0x1000B420 & 0xFFFF);
    lui        $5, (0x1000B400 >> 16);
    sw         $3, 0x0($16);
    ori        $5, $5, (0x1000B400 & 0xFFFF);
    lui        $7, (0x10002010 >> 16);
    lw         $3, 0x0($6);
    ori        $7, $7, (0x10002010 & 0xFFFF);
    sw         $3, 0x4($16);
    lw         $2, 0x0($4);
    sw         $2, 0x8($16);
    lw         $3, 0x0($5);
    sw         $3, 0xC($16);
  L00115C78:
    lw         $2, 0x0($7);
    andi       $2, $2, 0xF0;
    nop;
    nop;
    nop;
    bnez       $2, L00115C78;
    nop;
    jal        DmaIpuFromSetChcr_115b28;
    daddu     $4, $0, $0;
    lui        $2, (0x1000B010 >> 16);
    lui        $7, (0x1000B020 >> 16);
    ori        $2, $2, (0x1000B010 & 0xFFFF);
    ori        $7, $7, (0x1000B020 & 0xFFFF);
    lw         $3, 0x0($2);
    lui        $5, (0x1000B000 >> 16);
    ori        $5, $5, (0x1000B000 & 0xFFFF);
    lui        $6, (0x10002020 >> 16);
    sw         $3, 0x10($16);
    ori        $6, $6, (0x10002020 & 0xFFFF);
    lui        $4, (0x10002010 >> 16);
    ld         $31, 0x10($29);
    lw         $3, 0x0($7);
    ori        $4, $4, (0x10002010 & 0xFFFF);
    sw         $3, 0x14($16);
    lw         $2, 0x0($5);
    sw         $2, 0x18($16);
    lw         $3, 0x0($6);
    sw         $3, 0x1C($16);
    lw         $2, 0x0($4);
    sw         $2, 0x20($16);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
