#include "types.h"

extern void iSignalSema(void);

asm void iRotateThreadReadyQueue_117500(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sltiu      $2, $16, 0x80;
    beqz       $2, L00117528;
    sd        $31, 0x10($29);
    lui        $2, 0x44;
    lw         $3, 0x61F8($2);
    bnez       $3, L00117530;
    lui       $3, 0x48;
  L00117528:
    b          L0011756C;
    addiu     $2, $0, -0x1;
  L00117530:
    lui        $5, 0x48;
    addiu      $3, $3, 0x5FC8;
    lw         $4, 0x5FC0($5);
    lw         $2, 0x4($3);
    addiu      $7, $0, 0x1;
    andi       $2, $2, 0x1FF;
    sll        $6, $2, 1;
    addiu      $2, $2, 0x1;
    addu       $5, $3, $6;
    sw         $2, 0x4($3);
    sb         $7, 0x8($5);
    daddu      $3, $5, $0;
    jal        iSignalSema;
    sb        $16, 0x9($3);
    daddu      $2, $16, $0;
  L0011756C:
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
