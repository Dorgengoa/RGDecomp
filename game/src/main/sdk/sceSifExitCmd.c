#include "types.h"

extern void DisableDmac_117150(void);
extern void RemoveDmacHandler(void);

asm void sceSifExitCmd(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        DisableDmac_117150;
    addiu     $4, $0, 0x5;
    lui        $3, 0x48;
    addiu      $4, $0, 0x5;
    jal        RemoveDmacHandler;
    lw        $5, 0x6914($3);
    lui        $3, 0x44;
    ld         $31, 0x0($29);
    sw         $0, 0x6208($3);
    jr         $31;
    addiu     $29, $29, 0x10;
}
