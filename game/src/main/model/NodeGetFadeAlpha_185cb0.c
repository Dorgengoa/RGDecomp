/* rgp:protos */
#define RGP_SELF_NodeGetFadeAlpha_185cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x50];
    s32 m50;
    f32 m54;
};

f32 NodeGetFadeAlpha_185cb0(struct Obj0 *p0)
{
    s32 t0;
    f32 t1;

    t0 = p0->m50;
    if (t0 != 0) {
        t1 = p0->m54;
        return t1;
    }
    return 1.0f;
}
