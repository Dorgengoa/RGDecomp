/* rgp:protos */
#define RGP_SELF_PoolGetUsedElem_36acb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj0 { u8 pad000[0x8]; s32 m08; u8 pad00C[0x4]; s32 m10; s32 m14; u8 pad018[0x8]; s32 m20; };

s32 PoolGetUsedElem_36acb0(struct Obj0 *p0, s32 p1)
{
    s32 w;
    s32 b;
    s32 ok;
    s32 t2;

    if ((u32)p1 >= (u32)p0->m14) {
        return 0;
    }
    if ((u32)p1 >= (u32)p0->m14) {
        ok = 0;
    } else {
        w = p1 / 32;
        b = p1 % 32;
        t2 = *(s32 *)(p0->m20 + w * 4);
        ok = ((t2 & (1 << b)) != 0);
    }
    if (ok != 0) {
        return p0->m08 + p1 * p0->m10;
    }
    return 0;
}
