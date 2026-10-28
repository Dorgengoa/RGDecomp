/* rgp:protos */
#define RGP_SELF_AiCmdVecLength_2cc4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4_002cc4c0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_002cc4c0;

typedef struct S8_002cc4c0 {
    u8 b[8];
} S8_002cc4c0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdVecLength_2cc4c0(S8_002cc4c0 *p0, s32 p1)
{
    Vec4_002cc4c0 v0 __attribute__((aligned(16)));
    Vec4_002cc4c0 v1 __attribute__((aligned(16)));

    ScriptSlotsToVec4_2cc920(&v0, p0);
    v0.w = 1.0f;
    p0 += 3;
    if (p1 == 4) {
        ScriptSlotStoreFloatRef_2cc8e0(p0++, VecLength_13d4a0(&v0));
    }
    if (p1 == 7) {
        ScriptSlotsToVec4_2cc920(&v1, p0);
        v1.w = 1.0f;
        p0 = (S8_002cc4c0 *)((u8 *)p0 + 0x18);
        ScriptSlotStoreFloatRef_2cc8e0(p0, VecDistance_13d3d0(&v0, &v1));
    }
    return 1;
}
