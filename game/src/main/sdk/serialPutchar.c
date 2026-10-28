#include "types.h"

extern void kputchar(void);

asm void serialPutchar(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $2, $0, 0xA;
    bne        $4, $2, L00118110;
    sd        $31, 0x0($29);
    jal        kputchar;
    addiu     $4, $0, 0xD;
    ld         $31, 0x0($29);
    addiu      $4, $0, 0xA;
    j          kputchar;
    addiu     $29, $29, 0x10;
  L00118110:
    ld         $31, 0x0($29);
    j          kputchar;
    addiu     $29, $29, 0x10;
}
