/* rgp:protos */
#define RGP_SELF_AiCmdVecRotateY_2cbcd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdVecRotateY_2cbcd0(u8 *p0)
{
    f32 v[4] __attribute__((aligned(16)));
    f32 m[16] __attribute__((aligned(16)));

    v[0] = *(f32 *)(*(s32 *)(p0 + 0x4) + 4);
    v[1] = *(f32 *)(*(s32 *)(p0 + 0xC) + 4);
    v[2] = *(f32 *)(*(s32 *)(p0 + 0x14) + 4);
    v[3] = 1.0f;
    MtxRotY_13ce20(m, ScriptSlotGetFloat_2cc9a0(p0 + 0x18));
    MtxMulVec4_13c900(v, m, v);
    ScriptSlotStoreVec3_2cc8a0(p0, v);
    return 1;
}
