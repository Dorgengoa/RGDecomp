#include "types.h"

extern void Deci2Call(void);

asm void sceDeci2ExSend(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $2, $5, $0;
    andi       $6, $6, 0xFFFF;
    sw         $4, 0x0($29);
    sd         $31, 0x10($29);
    daddu      $5, $29, $0;
    sw         $2, 0x4($29);
    addiu      $4, $0, -0x6;
    jal        Deci2Call;
    sw        $6, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
