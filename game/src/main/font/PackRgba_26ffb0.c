/* rgp:protos */
#define RGP_SELF_PackRgba_26ffb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef union U_FUN_0026ffb0 {
    u8 b[8];
    u64 q;
} U_FUN_0026ffb0;

void PackRgba_26ffb0(u64 *out, u32 v)
{
    U_FUN_0026ffb0 u __attribute__((aligned(16)));

    u.b[0] = v;
    u.b[1] = (v & 0xFF00) >> 8;
    u.b[2] = (v & 0xFF0000) >> 16;
    u.b[3] = (v & 0xFF000000) >> 24;
    *out = u.q;
}
