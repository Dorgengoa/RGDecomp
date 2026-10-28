#include "types.h"

extern void Deci2Call(void);

asm void Deci2Related_117948(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    andi       $4, $4, 0xFF;
    sw         $5, 0x4($29);
    sw         $4, 0x0($29);
    daddu      $5, $29, $0;
    sd         $31, 0x20($29);
    addiu      $4, $0, 0x20;
    jal        Deci2Call;
    sw        $6, 0x8($29);
    ld         $31, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
