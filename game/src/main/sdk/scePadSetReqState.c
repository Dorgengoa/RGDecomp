#include "types.h"

extern void DisableIntr_120660(void);
extern void scePadGetDmaStr(void);
extern void SyncDCache(void);
extern void EnableIntr_1206b0(void);

asm void scePadSetReqState(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    addiu      $3, $0, 0x70;
    sd         $17, 0x10($29);
    lui        $2, 0x49;
    sd         $18, 0x20($29);
    daddu      $17, $4, $0;
    daddu      $18, $5, $0;
    addiu      $4, $0, 0x1C;
    mult1      $3, $17, $3;
    mult       $4, $18, $4;
    sd         $19, 0x30($29);
    addiu      $2, $2, -0x12B0;
    sd         $31, 0x40($29);
    sd         $16, 0x0($29);
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    bnez       $3, L0012B97C;
    daddu     $19, $6, $0;
    b          L0012B9C0;
    daddu     $2, $0, $0;
  L0012B97C:
    jal        DisableIntr_120660;
    nop;
    daddu      $6, $0, $0;
    daddu      $16, $2, $0;
    daddu      $4, $17, $0;
    jal        scePadGetDmaStr;
    daddu     $5, $18, $0;
    daddu      $4, $2, $0;
    sb         $19, 0x71($2);
    jal        SyncDCache;
    addiu     $5, $4, 0x7F;
    addiu      $2, $0, 0x1;
    bne        $16, $2, L0012B9C4;
    ld        $31, 0x40($29);
    jal        EnableIntr_1206b0;
    nop;
    addiu      $2, $0, 0x1;
  L0012B9C0:
    ld         $31, 0x40($29);
  L0012B9C4:
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
