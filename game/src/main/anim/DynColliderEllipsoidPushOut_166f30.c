/* rgp:protos */
#define RGP_SELF_DynColliderEllipsoidPushOut_166f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T166f30 {
    u8  pad000[0x10];
    u8  m10[0x40];
    u8  m50[0xD0];
    u8  m120[0x10];
    f32 f130;
    f32 f134;
    f32 f138;
} T166f30;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DynColliderEllipsoidPushOut_166f30(T166f30 *self, f32 *out)
{
    f32 b[4] __attribute__((aligned(16)));
    f32 a[4] __attribute__((aligned(16)));

    out[3] = 1.0f;
    MtxMulVec4_13c900(a, self->m50, out);
    VecSub_13be40(b, a, self->m120);
    b[0] = b[0] / self->f130;
    b[1] = b[1] / self->f134;
    b[2] = b[2] / self->f138;
    if (!(VecLength_13d4a0(b) < 1.0f)) {
        return 0;
    }
    {
        VecNormalize_13bd90(b, b);
        b[0] = b[0] * self->f130;
        b[1] = b[1] * self->f134;
        b[2] = b[2] * self->f138;
        VecAdd_13be20(a, self->m120, b);
        a[3] = 1.0f;
        MtxMulVec4_13c900(out, self->m10, a);
        return 1;
    }
}
