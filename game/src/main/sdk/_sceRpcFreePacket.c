#include "types.h"

asm void _sceRpcFreePacket(void)
{
    .set noreorder;
    lw         $3, 0x10($4);
    lui        $2, (0xFFFFFFFE >> 16);
    ori        $2, $2, (0xFFFFFFFE & 0xFFFF);
    sw         $0, 0x18($4);
    and        $3, $3, $2;
    jr         $31;
    sw        $3, 0x10($4);
}
