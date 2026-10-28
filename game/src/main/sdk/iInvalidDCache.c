#include "types.h"

extern void _sceIDC(void);

asm void iInvalidDCache(void)
{
    .set noreorder;
    lui        $2, (0xFFFFFFC0 >> 16);
    ori        $2, $2, (0xFFFFFFC0 & 0xFFFF);
    and        $5, $5, $2;
    j          _sceIDC;
    and       $4, $4, $2;
}
