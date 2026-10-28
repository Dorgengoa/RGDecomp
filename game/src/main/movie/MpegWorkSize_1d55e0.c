/* rgp:protos */
#define RGP_SELF_MpegWorkSize_1d55e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* `bgez` + `addiu 1` + `sra 1` is a SIGNED divide by two. */
s32 MpegWorkSize_1d55e0(s32 a, s32 b, s32 c)
{
    return b * c * 9 / 2 + 0x2800;
}
