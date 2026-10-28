/* rgp:protos */
#define RGP_SELF_DynColliderCylinderPushOut_166da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x10];
    f32 m10[16];
    f32 m50[16];
    u8 pad90[0x90];
    f32 m120[4];
    f32 m130[3];
    u8 pad13C[4];
    s32 m140;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DynColliderCylinderPushOut_166da0(Obj *o, f32 *v)
{
    f32 b[4] __attribute__((aligned(16)));
    f32 a[4] __attribute__((aligned(16)));
    f32 keep;
    f32 c;

    v[3] = 1.0f;
    MtxMulVec4_13c900(a, o->m50, v);
    VecSub_13be40(b, a, o->m120);
    b[0] /= o->m130[0];
    b[1] /= o->m130[1];
    b[2] /= o->m130[2];
    c = b[o->m140];
    if (1.0f < c) {
        return 0;
    }
    if (!(-1.0f <= c)) {
        return 0;
    }
    b[o->m140] = 0.0f;
    if (!(VecLength_13d4a0(b) < 1.0f)) {
        return 0;
    }
    VecNormalize_13bd90(b, b);
    b[0] *= o->m130[0];
    b[1] *= o->m130[1];
    b[2] *= o->m130[2];
    keep = a[o->m140];
    VecAdd_13be20(a, o->m120, b);
    a[o->m140] = keep;
    a[3] = 1.0f;
    MtxMulVec4_13c900(v, o->m10, a);
    return 1;
}
