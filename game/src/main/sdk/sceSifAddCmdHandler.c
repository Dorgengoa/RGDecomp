#include "types.h"

asm void sceSifAddCmdHandler(void)
{
    .set noreorder;
    daddu      $2, $4, $0;
    bgez       $2, L0011972C;
    daddu     $7, $5, $0;
    lui        $3, (0x7FFFFFFF >> 16);
    addiu      $5, $0, 0xC;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    lui        $4, 0x48;
    and        $3, $2, $3;
    addiu      $4, $4, 0x6918;
    mult       $3, $3, $5;
    lw         $2, 0xC($4);
    addu       $2, $3, $2;
    sw         $6, 0x4($2);
    sw         $7, 0x0($2);
    daddu      $5, $28, $0;
    b          L00119754;
    lw        $2, 0xC($4);
  L0011972C:
    addiu      $3, $0, 0xC;
    lui        $4, 0x48;
    mult       $3, $2, $3;
    addiu      $4, $4, 0x6918;
    lw         $2, 0x14($4);
    addu       $2, $3, $2;
    sw         $6, 0x4($2);
    sw         $7, 0x0($2);
    daddu      $5, $28, $0;
    lw         $2, 0x14($4);
  L00119754:
    addu       $3, $3, $2;
    jr         $31;
    sw        $5, 0x8($3);
}
