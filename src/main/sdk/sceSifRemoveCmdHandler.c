#include "types.h"

asm void sceSifRemoveCmdHandler(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    bgez       $6, L00119794;
    addiu     $2, $0, 0xC;
    lui        $2, (0x7FFFFFFF >> 16);
    addiu      $5, $0, 0xC;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    lui        $3, 0x48;
    and        $2, $6, $2;
    lw         $4, 0x6924($3);
    mult       $2, $2, $5;
    addu       $2, $2, $4;
    jr         $31;
    sw        $0, 0x0($2);
  L00119794:
    lui        $4, 0x48;
    mult       $2, $6, $2;
    lw         $3, 0x692C($4);
    addu       $2, $2, $3;
    jr         $31;
    sw        $0, 0x0($2);
}
