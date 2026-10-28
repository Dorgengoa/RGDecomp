/* rgp:protos */
#define RGP_SELF_AiCmdVecLengthXZ_2cc360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4_002cc360 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_002cc360;

typedef struct S8_002cc360 {
    u8 b[8];
} S8_002cc360;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdVecLengthXZ_2cc360(S8_002cc360 *p0, s32 p1)
{
    Vec4_002cc360 v0 __attribute__((aligned(16)));
    Vec4_002cc360 v1 __attribute__((aligned(16)));

    ScriptSlotsToVec4_2cc920(&v0, p0);
    v0.w = 1.0f;
    p0 += 3;
    if (p1 == 4) {
        ScriptSlotStoreFloatRef_2cc8e0(p0++, VecLengthXZ_13d470(&v0));
    }
    if (p1 == 7) {
        ScriptSlotsToVec4_2cc920(&v1, p0);
        v1.w = 1.0f;
        p0 = (S8_002cc360 *)((u8 *)p0 + 0x18);
        ScriptSlotStoreFloatRef_2cc8e0(p0, VecDistanceXZ_13d390(&v0, &v1));
    }
    return 1;
}
