#include "types.h"

extern void SignalSema(void);

asm void MallocUnlock_131ca0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $3, 0x45;
    sd         $31, 0x0($29);
    addiu      $3, $3, -0x633C;
    lw         $2, 0x0($3);
    addiu      $2, $2, -0x1;
    bnez       $2, L00131CE0;
    sw        $2, 0x0($3);
    lui        $2, 0x44;
    ld         $31, 0x0($29);
    lw         $4, 0x6930($2);
    lui        $5, 0x45;
    addiu      $3, $0, -0x1;
    sw         $3, -0x6340($5);
    j          SignalSema;
    addiu     $29, $29, 0x10;
  L00131CE0:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
