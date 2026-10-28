/* rgp:protos */
#define RGP_SELF_ModelObjGetFadeAlpha_186f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x1DC];
    s32 m1DC;
    f32 m1E0;
};

f32 ModelObjGetFadeAlpha_186f40(struct Obj0 *p0)
{
    s32 t0;
    f32 t1;

    t0 = p0->m1DC;
    if (t0 != 0) {
        t1 = p0->m1E0;
        return t1;
    }
    return 1.0f;
}
