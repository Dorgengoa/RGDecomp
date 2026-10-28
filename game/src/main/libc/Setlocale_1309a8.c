#include "types.h"

extern void SetlocaleR_130908(void);

asm void Setlocale_1309a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    daddu      $6, $5, $0;
    daddu      $5, $4, $0;
    lw         $4, -0x67A8($2);
    ld         $31, 0x0($29);
    j          SetlocaleR_130908;
    addiu     $29, $29, 0x10;
}
