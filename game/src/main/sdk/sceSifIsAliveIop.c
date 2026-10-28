#include "types.h"

extern void sceSifGetReg(void);

asm void sceSifIsAliveIop(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        sceSifGetReg;
    addiu     $4, $0, 0x4;
    lui        $3, (0x10000 >> 16);
    ld         $31, 0x0($29);
    and        $2, $2, $3;
    sltu       $2, $0, $2;
    jr         $31;
    addiu     $29, $29, 0x10;
}
