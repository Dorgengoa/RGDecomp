#include "types.h"

extern void strcpy(void);

asm void scePadStateIntToStr(void)
{
    .set noreorder;
    sltiu      $2, $4, 0x8;
    beqz       $2, L0012B918;
    lui       $2, 0x45;
    lui        $2, 0x45;
    sll        $3, $4, 2;
    addiu      $2, $2, -0x6AE8;
    daddu      $4, $5, $0;
    addu       $3, $3, $2;
    j          strcpy;
    lw        $5, 0x0($3);
  L0012B918:
    lbu        $3, 0x7D78($2);
    jr         $31;
    sb        $3, 0x0($5);
}
