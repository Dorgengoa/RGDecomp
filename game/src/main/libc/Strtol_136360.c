#include "types.h"
extern void *const D_00449858;   /* _impure_ptr */
extern s32 StrtolR_136128(void *r, s32 a, s32 b, s32 c);

asm s32 Strtol_136360(s32 a, s32 b, s32 c)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $3, 0x45;
    sd         $31, 0x0($29);
    daddu      $2, $5, $0;
    daddu      $5, $4, $0;
    lw         $4, -0x67A8($3);
    ld         $31, 0x0($29);
    daddu      $7, $6, $0;
    daddu      $6, $2, $0;
    j          StrtolR_136128;
    addiu     $29, $29, 0x10;
}
