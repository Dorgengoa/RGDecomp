#include "types.h"

extern void DisableIntr_120660(void);
extern void iInvalidDCache(void);
extern void EnableIntr_1206b0(void);

asm void scePadGetDmaStr(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    daddu      $18, $6, $0;
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $19, 0x30($29);
    sd         $31, 0x40($29);
    jal        DisableIntr_120660;
    daddu     $16, $5, $0;
    daddu      $19, $2, $0;
    addiu      $3, $0, 0x70;
    addiu      $2, $0, 0x1C;
    mult1      $17, $17, $3;
    mult       $16, $16, $2;
    lui        $2, 0x49;
    addiu      $2, $2, -0x12B0;
    addu       $16, $16, $17;
    addu       $16, $16, $2;
    lw         $16, 0x0($16);
    daddu      $4, $16, $0;
    jal        iInvalidDCache;
    addiu     $5, $16, 0xFF;
    lw         $3, 0x58($16);
    lw         $2, 0xD8($16);
    beqz       $18, L0012B770;
    slt       $3, $3, $2;
    sll        $17, $3, 7;
    daddu      $6, $18, $0;
    addu       $3, $17, $16;
    or         $2, $3, $6;
    andi       $2, $2, 0x7;
    beqz       $2, L0012B734;
    addiu     $2, $3, 0x80;
  L0012B6D8:
    ldl        $4, 0x7($3);
    ldr        $4, 0x0($3);
    ldl        $5, 0xF($3);
    ldr        $5, 0x8($3);
    ldl        $7, 0x17($3);
    ldr        $7, 0x10($3);
    ldl        $8, 0x1F($3);
    ldr        $8, 0x18($3);
    sdl        $4, 0x7($6);
    sdr        $4, 0x0($6);
    sdl        $5, 0xF($6);
    sdr        $5, 0x8($6);
    sdl        $7, 0x17($6);
    sdr        $7, 0x10($6);
    sdl        $8, 0x1F($6);
    sdr        $8, 0x18($6);
    addiu      $3, $3, 0x20;
    addiu      $6, $6, 0x20;
    nop;
    bne        $3, $2, L0012B6D8;
    nop;
    b          L0012B778;
    addiu     $2, $0, 0x1;
  L0012B734:
    ld         $4, 0x0($3);
    ld         $5, 0x8($3);
    ld         $7, 0x10($3);
    ld         $8, 0x18($3);
    sd         $4, 0x0($6);
    sd         $5, 0x8($6);
    sd         $7, 0x10($6);
    sd         $8, 0x18($6);
    addiu      $3, $3, 0x20;
    addiu      $6, $6, 0x20;
    nop;
    bne        $3, $2, L0012B734;
    nop;
    b          L0012B778;
    addiu     $2, $0, 0x1;
  L0012B770:
    sll        $17, $3, 7;
    addiu      $2, $0, 0x1;
  L0012B778:
    bne        $19, $2, L0012B78C;
    addu      $2, $16, $17;
    jal        EnableIntr_1206b0;
    nop;
    addu       $2, $16, $17;
  L0012B78C:
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
