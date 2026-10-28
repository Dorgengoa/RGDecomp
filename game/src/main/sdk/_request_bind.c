#include "types.h"

extern void isceSifSendCmd(void);

asm void _request_bind(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $5, $7, $0;
    lui        $4, (0x80000008 >> 16);
    sd         $31, 0x0($29);
    ori        $4, $4, (0x80000008 & 0xFFFF);
    addiu      $6, $0, 0x40;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    jal        isceSifSendCmd;
    daddu     $9, $0, $0;
    addiu      $3, $0, 0x800;
    ld         $31, 0x0($29);
    movn       $3, $0, $2;
    daddu      $2, $3, $0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
