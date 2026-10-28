/* rgp:protos */
#define RGP_SELF_HitShapeSetWorldSphere_317150 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
typedef struct P317150 { u8 m00; u8 pad001[0xF]; u128 m10; } P317150;
void HitShapeSetWorldSphere_317150(P317150 *p, u128 *q, f32 f)
{
    p->m00 = 4;
    p->m10 = *q;
    *(f32 *)((u8 *)p + 0x1C) = f;
}
