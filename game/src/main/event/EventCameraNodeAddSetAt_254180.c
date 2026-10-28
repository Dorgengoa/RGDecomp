/* rgp:protos */
#define RGP_SELF_EventCameraNodeAddSetAt_254180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
    u8 pad004[0x1C];
    u8 m20[0x10];
};

void EventCameraNodeAddSetAt_254180(s32 p0, const void *p1)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_254450(p0);
    if (r0 != 0) {
        r0->m00 = 3;
        sceVu0CopyVector(r0->m20, p1);
    }
}
