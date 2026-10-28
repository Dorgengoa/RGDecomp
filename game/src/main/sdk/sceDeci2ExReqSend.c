#include "types.h"

extern void Deci2Call(void);

asm void sceDeci2ExReqSend(void)
{
    .set noreorder;
    sll        $5, $5, 24;
    addiu      $29, $29, -0x20;
    sra        $5, $5, 24;
    sw         $4, 0x0($29);
    sw         $5, 0x4($29);
    addiu      $4, $0, -0x7;
    sd         $31, 0x10($29);
    jal        Deci2Call;
    daddu     $5, $29, $0;
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
