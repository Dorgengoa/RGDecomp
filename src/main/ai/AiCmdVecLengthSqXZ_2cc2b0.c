#include "types.h"

typedef struct Vec4_002cc2b0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_002cc2b0;

typedef struct S8_002cc2b0 {
    u8 b[8];
} S8_002cc2b0;

extern void ScriptSlotsToVec4_2cc920(Vec4_002cc2b0 *, S8_002cc2b0 *);
extern f32 VecLengthSqXZ_13d410(Vec4_002cc2b0 *);
extern f32 VecDistSqXZ_13d330(Vec4_002cc2b0 *, Vec4_002cc2b0 *);
extern void ScriptSlotStoreFloatRef_2cc8e0(S8_002cc2b0 *, f32);

s32 AiCmdVecLengthSqXZ_2cc2b0(S8_002cc2b0 *p0, s32 p1)
{
    Vec4_002cc2b0 v0;
    Vec4_002cc2b0 v1;

    ScriptSlotsToVec4_2cc920(&v0, p0);
    v0.w = 1.0f;
    p0 += 3;
    if (p1 == 4) {
        ScriptSlotStoreFloatRef_2cc8e0(p0++, VecLengthSqXZ_13d410(&v0));
    }
    if (p1 == 7) {
        ScriptSlotsToVec4_2cc920(&v1, p0);
        v1.w = 1.0f;
        p0 = (S8_002cc2b0 *)((u8 *)p0 + 0x18);
        ScriptSlotStoreFloatRef_2cc8e0(p0, VecDistSqXZ_13d330(&v0, &v1));
    }
    return 1;
}
