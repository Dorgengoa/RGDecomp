#include "types.h"

extern void FlushCache(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void IpuDmaSendChainMaybe_1106e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $4, $4, 0x118F;
    sd         $16, 0x0($29);
    srl        $4, $4, 4;
    sll        $16, $4, 4;
    sd         $31, 0x10($29);
    daddu      $11, $5, $0;
    daddu      $8, $6, $0;
    blez       $8, L0011077C;
    daddu     $10, $16, $0;
    lui        $9, (0xFFF40 >> 16);
    lui        $12, (0xFFFFFFF >> 16);
    ori        $9, $9, (0xFFF40 & 0xFFFF);
    ori        $12, $12, (0xFFFFFFF & 0xFFFF);
    addiu      $14, $0, 0x3;
    addiu      $13, $0, -0x1;
  L00110720:
    slt        $2, $9, $8;
    daddu      $7, $9, $0;
    movz       $7, $8, $2;
    daddu      $3, $0, $0;
    addiu      $6, $7, 0xF;
    addiu      $2, $7, 0x1E;
    slt        $5, $13, $6;
    subu       $8, $8, $7;
    movn       $2, $6, $5;
    and        $4, $11, $12;
    movn       $3, $14, $8;
    sra        $2, $2, 4;
    dsll32     $4, $4, 0;
    dsll       $3, $3, 28;
    dsll32     $2, $2, 0;
    or         $4, $4, $3;
    dsrl32     $2, $2, 0;
    or         $4, $4, $2;
    sd         $4, 0x0($10);
    sync;
    addu       $11, $11, $7;
    bgtz       $8, L00110720;
    addiu     $10, $10, 0x10;
  L0011077C:
    jal        FlushCache;
    daddu     $4, $0, $0;
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0xFFFFFFF >> 16);
    lui        $5, (0x1000B430 >> 16);
    ori        $3, $3, (0xFFFFFFF & 0xFFFF);
    ori        $5, $5, (0x1000B430 & 0xFFFF);
    and        $3, $16, $3;
    lui        $4, (0x1000B420 >> 16);
    sw         $3, 0x0($5);
    ori        $4, $4, (0x1000B420 & 0xFFFF);
    sw         $0, 0x0($4);
    lui        $3, (0x1000B400 >> 16);
    ori        $3, $3, (0x1000B400 & 0xFFFF);
    addiu      $4, $0, 0x105;
    sw         $4, 0x0($3);
    beqz       $2, L001107D4;
    ld        $31, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x20;
  L001107D4:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
