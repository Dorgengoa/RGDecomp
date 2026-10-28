/* rgp:protos */
#define RGP_SELF_FadeGetAlpha_186dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    f32 m18;
};

f32 FadeGetAlpha_186dc0(struct Obj0 *p0)
{
    s32 t0;
    f32 t1;

    t0 = p0->m14;
    if (t0 != 0) {
        t1 = p0->m18;
        return t1;
    }
    return 1.0f;
}
