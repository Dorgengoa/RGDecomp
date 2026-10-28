/* rgp:protos */
#define RGP_SELF_EventSubNodeAddJumpTo_2516b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    f32 m20;
    s32 m24;
};

void EventSubNodeAddJumpTo_2516b0(s32 p0, const void *p1, s32 p2, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e70(p0);
    if (r0 != 0) {
        r0->m00 = 9;
        sceVu0CopyVector(r0->m10, p1);
        r0->m20 = fa0;
        r0->m24 = p2;
    }
}
