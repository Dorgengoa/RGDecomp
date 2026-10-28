#include "types.h"

extern void _sceSifSendCmd(void);

asm void isceSifSendCmd(void)
{
    .set noreorder;
    daddu      $2, $6, $0;
    daddu      $3, $7, $0;
    daddu      $11, $8, $0;
    addiu      $29, $29, -0x10;
    daddu      $10, $9, $0;
    daddu      $6, $5, $0;
    sd         $31, 0x0($29);
    daddu      $7, $2, $0;
    daddu      $8, $3, $0;
    daddu      $9, $11, $0;
    jal        _sceSifSendCmd;
    addiu     $5, $0, 0x1;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
