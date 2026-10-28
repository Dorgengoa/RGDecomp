#include "types.h"
extern s32 D_00486AC0[];

asm s32 sceSifSetSreg(s32 index, s32 value)
{
    .set noreorder;
    lui        $2, 0x48;
    sll        $4, $4, 2;
    addiu      $2, $2, 0x6AC0;
    addu       $4, $4, $2;
    daddu      $2, $5, $0;
    jr         $31;
    sw        $5, 0x0($4);
}
