#include "types.h"

extern void serialPutchar(void);

asm void KprintfSerialPutcCb_119120(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $4, $6, $0;
    beqz       $4, L00119138;
    sd        $31, 0x0($29);
    jal        serialPutchar;
    nop;
  L00119138:
    ld         $31, 0x0($29);
    addiu      $2, $0, 0x1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
