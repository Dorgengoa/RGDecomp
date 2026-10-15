#include "types.h"
/* `bgez` + `addiu 1` + `sra 1` is a SIGNED divide by two. */
s32 MpegWorkSize_1d55e0(s32 a, s32 b, s32 c)
{
    return b * c * 9 / 2 + 0x2800;
}
