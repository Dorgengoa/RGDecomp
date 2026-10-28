#include "types.h"

extern void SetVTLBRefillHandler(void);

asm void SetTLBHandler_11fde0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    lui        $2, 0x44;
    sd         $16, 0x0($29);
    sd         $17, 0x10($29);
    lui        $16, 0x12;
    addiu      $16, $16, 0x300;
    daddu      $17, $4, $0;
    sw         $17, 0x65F8($2);
    daddu      $5, $16, $0;
    sd         $31, 0x20($29);
    jal        SetVTLBRefillHandler;
    addiu     $4, $0, 0x1;
    daddu      $5, $16, $0;
    jal        SetVTLBRefillHandler;
    addiu     $4, $0, 0x2;
    daddu      $5, $16, $0;
    jal        SetVTLBRefillHandler;
    addiu     $4, $0, 0x3;
    daddu      $2, $17, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
