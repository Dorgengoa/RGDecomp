#include "types.h"

extern void SignalR_134040(void);

asm void Signal_134250(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    daddu      $6, $5, $0;
    daddu      $5, $4, $0;
    lw         $4, -0x67A8($2);
    ld         $31, 0x0($29);
    j          SignalR_134040;
    addiu     $29, $29, 0x10;
}

