#include "types.h"

extern void GetThreadId(void);
extern void WaitSema(void);

asm void MallocLock_131c20(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $17, 0x8($29);
    sd         $31, 0x10($29);
    jal        GetThreadId;
    nop;
    lui        $3, 0x45;
    daddu      $16, $2, $0;
    addiu      $17, $3, -0x6340;
    lui        $2, 0x45;
    addiu      $4, $2, -0x633C;
    lw         $2, 0x0($17);
    bne        $2, $16, L00131C68;
    lui       $2, 0x44;
    lw         $2, 0x0($4);
    addiu      $2, $2, 0x1;
    b          L00131C88;
    sw        $2, 0x0($4);
  L00131C68:
    jal        WaitSema;
    lw        $4, 0x6930($2);
    lui        $3, 0x45;
    sw         $16, 0x0($17);
    addiu      $3, $3, -0x633C;
    lw         $2, 0x0($3);
    addiu      $2, $2, 0x1;
    sw         $2, 0x0($3);
  L00131C88:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
