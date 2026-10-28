#include "types.h"

extern void Deci2Call(void);

asm void sceDeci2Open(void)
{
    .set noreorder;
    lui        $2, 0x48;
    addiu      $29, $29, -0x20;
    lui        $3, (0x20000000 >> 16);
    addiu      $2, $2, 0x63D0;
    andi       $4, $4, 0xFFFF;
    or         $2, $2, $3;
    sw         $5, 0x4($29);
    sw         $4, 0x0($29);
    daddu      $5, $29, $0;
    sd         $31, 0x10($29);
    addiu      $4, $0, 0x1;
    sw         $6, 0x8($29);
    jal        Deci2Call;
    sw        $2, 0xC($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
