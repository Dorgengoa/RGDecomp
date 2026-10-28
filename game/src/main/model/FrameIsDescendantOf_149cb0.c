/* rgp:protos */
#define RGP_SELF_FrameIsDescendantOf_149cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj0 *m04;
};

s32 FrameIsDescendantOf_149cb0(struct Obj0 *p0, struct Obj0 *p1)
{
    struct Obj0 *t0;

    t0 = p0->m04;
    while (t0 != 0) {
        if (t0 == p1) {
            return 1;
        }
        t0 = t0->m04;
    }
    return 0;
}
