#include "types.h"

extern void LocaleconvR_130998(void);

asm void Localeconv_1309d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    lw         $4, -0x67A8($2);
    ld         $31, 0x0($29);
    j          LocaleconvR_130998;
    addiu     $29, $29, 0x10;
}
