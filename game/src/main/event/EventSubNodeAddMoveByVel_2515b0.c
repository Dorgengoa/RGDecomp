/* rgp:protos */
#define RGP_SELF_EventSubNodeAddMoveByVel_2515b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    s32 m20;
    s32 m24;
};

void EventSubNodeAddMoveByVel_2515b0(s32 p0, const void *p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e70(p0);
    if (r0 != 0) {
        r0->m00 = 0xB;
        sceVu0CopyVector(r0->m10, p1);
        r0->m20 = p2;
        r0->m24 = p3;
    }
}
