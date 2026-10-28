/* rgp:protos */
#define RGP_SELF_FogColRegWrite_156c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void FogColRegWrite_156c00(u8 *p0, s64 *p1)
{
    p1[0] = (s32)(p0[8] | (p0[9] << 8) | (p0[10] << 16));
    p1[1] = 0x3D;
}
