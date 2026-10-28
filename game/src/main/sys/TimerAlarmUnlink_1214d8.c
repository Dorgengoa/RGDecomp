#include "types.h"

asm void TimerAlarmUnlink_1214d8(void)
{
    .set noreorder;
    lw         $2, 0x4($4);
    beqz       $2, L001214EC;
    lw        $3, 0x0($4);
    b          L001214F4;
    sw        $3, 0x0($2);
  L001214EC:
    lui        $2, 0x44;
    sw         $3, 0x78C0($2);
  L001214F4:
    beql       $3, $0, L00121508;
    sw        $0, 0x4($4);
    lw         $2, 0x4($4);
    sw         $2, 0x4($3);
    sw         $0, 0x4($4);
  L00121508:
    jr         $31;
    daddu     $2, $3, $0;
}
