#include "types.h"
extern s32 D_00486AC0[];

asm s32 sceSifGetSreg(s32 index)
{
    .set noreorder;
    lui        $2, 0x48;
    sll        $4, $4, 2;
    addiu      $2, $2, 0x6AC0;
    addu       $4, $4, $2;
    jr         $31;
    lw        $2, 0x0($4);
}
