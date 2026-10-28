#include "types.h"

extern void iSignalSema(void);

asm void McGetInfoCb_12d160(void)
{
    .set noreorder;
    lui        $2, 0x49;
    lui        $3, (0x20000090 >> 16);
    lw         $5, -0xFD8($2);
    beqz       $5, L0012D17C;
    or        $4, $4, $3;
    lw         $2, (0x20000000 & 0xFFFF)($4);
    sw         $2, 0x0($5);
  L0012D17C:
    lui        $2, 0x49;
    lw         $3, -0xFD4($2);
    beqz       $3, L0012D198;
    lui       $2, 0x49;
    lw         $2, (0x20000004 & 0xFFFF)($4);
    sw         $2, 0x0($3);
    lui        $2, 0x49;
  L0012D198:
    lw         $3, -0xFD0($2);
    beqz       $3, L0012D1B0;
    lui       $2, 0x45;
    lw         $2, (0x20000090 & 0xFFFF)($4);
    sw         $2, 0x0($3);
    lui        $2, 0x45;
  L0012D1B0:
    j          iSignalSema;
    lw        $4, -0x6AA0($2);
}
