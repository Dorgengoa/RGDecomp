#include "types.h"
typedef unsigned __int128 u128;
typedef struct P317150 { u8 m00; u8 pad001[0xF]; u128 m10; } P317150;
void HitShapeSetWorldSphere_317150(P317150 *p, u128 *q, f32 f)
{
    p->m00 = 4;
    p->m10 = *q;
    *(f32 *)((u8 *)p + 0x1C) = f;
}
