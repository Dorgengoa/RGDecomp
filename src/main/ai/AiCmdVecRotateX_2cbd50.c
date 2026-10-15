#include "types.h"

extern f32 ScriptSlotGetFloat_2cc9a0(void *p);
extern void MtxRotX_13ce90(f32 *m, f32 a);
extern void MtxMulVec4_13c900(f32 *d, f32 *m, f32 *s);
extern void ScriptSlotStoreVec3_2cc8a0(void *p, f32 *v);

s32 AiCmdVecRotateX_2cbd50(u8 *p0)
{
    f32 v[4];
    f32 m[16];

    v[0] = *(f32 *)(*(s32 *)(p0 + 0x4) + 4);
    v[1] = *(f32 *)(*(s32 *)(p0 + 0xC) + 4);
    v[2] = *(f32 *)(*(s32 *)(p0 + 0x14) + 4);
    v[3] = 1.0f;
    MtxRotX_13ce90(m, ScriptSlotGetFloat_2cc9a0(p0 + 0x18));
    MtxMulVec4_13c900(v, m, v);
    ScriptSlotStoreVec3_2cc8a0(p0, v);
    return 1;
}
