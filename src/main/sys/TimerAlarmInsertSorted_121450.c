#include "types.h"

asm void TimerAlarmInsertSorted_121450(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    lui        $9, 0x44;
    ld         $2, 0x20($6);
    addiu      $5, $9, 0x78A8;
    ld         $3, 0x10($6);
    daddu      $8, $0, $0;
    ld         $4, 0x18($6);
    daddu      $2, $2, $3;
    lw         $5, 0x18($5);
    b          L00121484;
    dsubu     $7, $2, $4;
    nop;
  L00121480:
    lw         $5, 0x0($8);
  L00121484:
    beql       $5, $0, L001214B0;
    sw        $8, 0x4($6);
    ld         $2, 0x20($5);
    ld         $3, 0x10($5);
    ld         $4, 0x18($5);
    daddu      $2, $2, $3;
    dsubu      $2, $2, $4;
    sltu       $2, $7, $2;
    beql       $2, $0, L00121480;
    daddu     $8, $5, $0;
    sw         $8, 0x4($6);
  L001214B0:
    beqz       $5, L001214BC;
    sw        $5, 0x0($6);
    sw         $6, 0x4($5);
  L001214BC:
    beqz       $8, L001214CC;
    addiu     $2, $9, 0x78A8;
    jr         $31;
    sw        $6, 0x0($8);
  L001214CC:
    jr         $31;
    sw        $6, 0x18($2);
}
