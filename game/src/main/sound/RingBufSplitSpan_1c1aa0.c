/* rgp:protos */
#define RGP_SELF_RingBufSplitSpan_1c1aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 {
    s32 m00;
    s32 m04;
};

struct Obj1 {
    s32 m00;
    s32 m04;
};

s32 RingBufSplitSpan_1c1aa0(struct Obj0 *p0, struct Obj1 *p1, u32 p2, u32 p3, u32 p4)
{
    u32 end;

    p0->m04 = 0;
    p0->m00 = 0;
    p1->m04 = 0;
    p1->m00 = 0;
    if (p3 == 0) {
        goto fail;
    }
    if (p4 != 0) {
        goto ok;
    }
fail:
    return 0;
ok:
    end = p2 + p3;
    if (end > p4) {
        goto split;
    }
    p0->m00 = p2;
    p1->m00 = p3;
    return 1;
split:
    p0->m00 = p2;
    p1->m00 = p4 - p2;
    p0->m04 = 0;
    p1->m04 = p3 - p1->m00;
    return 2;
}
