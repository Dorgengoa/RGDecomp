#include "types.h"
typedef unsigned __int128 u128;
typedef struct P3171D0 { u8 m00; u8 pad001[0x7]; s32 m08; u8 pad00C[0x4]; u128 m10; } P3171D0;
void HitShapeSetSphere_3171d0(P3171D0 *p, u128 *q, s32 c, f32 f)
{
    p->m00 = 1;
    p->m08 = c;
    p->m10 = *q;
    *(f32 *)((u8 *)p + 0x1C) = f;
}
