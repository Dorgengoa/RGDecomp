#include "types.h"

typedef union U_FUN_0026ffb0 {
    u8 b[8];
    u64 q;
} U_FUN_0026ffb0;

void PackRgba_26ffb0(u64 *out, u32 v)
{
    U_FUN_0026ffb0 u;

    u.b[0] = v;
    u.b[1] = (v & 0xFF00) >> 8;
    u.b[2] = (v & 0xFF0000) >> 16;
    u.b[3] = (v & 0xFF000000) >> 24;
    *out = u.q;
}
