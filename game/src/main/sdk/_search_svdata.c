#include "types.h"

asm void _search_svdata(void)
{
    .set noreorder;
    lw         $5, 0x28($5);
    beqz       $5, L0011A1EC;
    nop;
    lw         $3, 0x8($5);
  L0011A1B8:
    beql       $3, $0, L0011A1E4;
    lw        $5, 0x14($5);
    lw         $2, 0x0($3);
    nop;
  L0011A1C8:
    bnel       $2, $4, L0011A1D8;
    lw        $3, 0x38($3);
    jr         $31;
    daddu     $2, $3, $0;
  L0011A1D8:
    bnel       $3, $0, L0011A1C8;
    lw        $2, 0x0($3);
    lw         $5, 0x14($5);
  L0011A1E4:
    bnel       $5, $0, L0011A1B8;
    lw        $3, 0x8($5);
  L0011A1EC:
    jr         $31;
    daddu     $2, $0, $0;
}
