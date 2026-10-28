#include "types.h"

extern void sceSifExitCmd(void);

asm void sceSifExitRpc(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        sceSifExitCmd;
    nop;
    lui        $2, 0x44;
    ld         $31, 0x0($29);
    sw         $0, 0x6210($2);
    jr         $31;
    addiu     $29, $29, 0x10;
}
