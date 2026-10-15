#include "types.h"

asm void StdioStdInit_12f6a8(void)
{
    .set noreorder;
    lui        $2, 0x13;
    lui        $3, 0x13;
    lui        $8, 0x13;
    lui        $9, 0x13;
    addiu      $2, $2, 0x4448;
    addiu      $3, $3, 0x44B0;
    addiu      $8, $8, 0x4530;
    addiu      $9, $9, 0x4598;
    sw         $7, 0x54($4);
    sh         $5, 0xC($4);
    sh         $6, 0xE($4);
    sw         $2, 0x20($4);
    sw         $3, 0x24($4);
    sw         $8, 0x28($4);
    sw         $9, 0x2C($4);
    sw         $0, 0x0($4);
    sw         $0, 0x4($4);
    sw         $0, 0x8($4);
    sw         $0, 0x10($4);
    sw         $0, 0x14($4);
    sw         $0, 0x18($4);
    jr         $31;
    sw        $4, 0x1C($4);
}
