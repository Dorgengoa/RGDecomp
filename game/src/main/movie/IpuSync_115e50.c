#include "types.h"

asm void IpuSync_115e50(void)
{
    .set noreorder;
    beqz       $4, L00115E6C;
    daddu     $3, $0, $0;
    addiu      $2, $0, 0x1;
    beq        $4, $2, L00115E9C;
    daddu     $2, $3, $0;
    b          L00115EB0;
    nop;
  L00115E6C:
    lui        $3, (0x10002010 >> 16);
    ori        $3, $3, (0x10002010 & 0xFFFF);
    nop;
  L00115E78:
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    nop;
    bltz       $2, L00115E78;
    nop;
    b          L00115EAC;
    daddu     $3, $0, $0;
  L00115E9C:
    lui        $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lw         $3, 0x0($2);
    srl        $3, $3, 31;
  L00115EAC:
    daddu      $2, $3, $0;
  L00115EB0:
    jr         $31;
    nop;
}
