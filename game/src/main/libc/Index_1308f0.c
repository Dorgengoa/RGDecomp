#include "types.h"

extern void Strchr_1347c0(void);

asm void Index_1308f0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          Strchr_1347c0;
    addiu     $29, $29, 0x10;
}
