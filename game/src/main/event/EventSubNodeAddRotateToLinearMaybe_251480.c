/* rgp:protos */
#define RGP_SELF_EventSubNodeAddRotateToLinearMaybe_251480 1
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
};

void EventSubNodeAddRotateToLinearMaybe_251480(s32 p0, const void *p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e10(p0);
    if (r0 != 0) {
        r0->m00 = 0xF;
        sceVu0CopyVector(r0->m10, p1);
        r0->m20 = p2;
    }
}
