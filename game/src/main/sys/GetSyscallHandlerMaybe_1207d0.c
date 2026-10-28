#include "types.h"

extern void KCopy_120738(void);

asm void GetSyscallHandlerMaybe_1207d0(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $29, $29, -0x20;
    lw         $5, 0x6918($2);
    sll        $3, $4, 2;
    sd         $31, 0x10($29);
    daddu      $4, $29, $0;
    addiu      $6, $0, 0x4;
    jal        KCopy_120738;
    addu      $5, $5, $3;
    lw         $2, 0x0($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
