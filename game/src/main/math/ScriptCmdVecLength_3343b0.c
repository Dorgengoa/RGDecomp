/* rgp:protos */
#define RGP_SELF_ScriptCmdVecLength_3343b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4_003343b0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_003343b0;

typedef struct S8_003343b0 {
    u8 b[8];
} S8_003343b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdVecLength_3343b0(S8_003343b0 *p0, s32 p1)
{
    Vec4_003343b0 v0 __attribute__((aligned(16)));
    Vec4_003343b0 v1 __attribute__((aligned(16)));

    ScriptSlotsToVec4_334810(&v0, p0);
    v0.w = 1.0f;
    p0 += 3;
    if (p1 == 4) {
        ScriptSlotStoreFloatRef_3347d0(p0++, VecLength_13d4a0(&v0));
    }
    if (p1 == 7) {
        ScriptSlotsToVec4_334810(&v1, p0);
        v1.w = 1.0f;
        p0 = (S8_003343b0 *)((u8 *)p0 + 0x18);
        ScriptSlotStoreFloatRef_3347d0(p0, VecDistance_13d3d0(&v0, &v1));
    }
    return 1;
}
