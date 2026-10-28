#include "types.h"

extern void isceSifSendCmd(void);

asm void _request_rdata(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $5, $7, $0;
    sd         $31, 0x0($29);
    lui        $4, (0x80000008 >> 16);
    ori        $4, $4, (0x80000008 & 0xFFFF);
    addiu      $6, $0, 0x40;
    lw         $7, 0x24($5);
    lw         $8, 0x28($5);
    jal        isceSifSendCmd;
    lw        $9, 0x2C($5);
    addiu      $3, $0, 0x800;
    ld         $31, 0x0($29);
    movn       $3, $0, $2;
    daddu      $2, $3, $0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
