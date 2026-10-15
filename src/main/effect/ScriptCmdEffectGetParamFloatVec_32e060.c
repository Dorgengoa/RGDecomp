#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptSlotGetInt_3348b0(E8 *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(void *, void *);
extern void EffectGetParamFloatVec_2e0240(s32, void *, s32, f32 *);
extern void ScriptSlotStoreFloatRef_3347d0(E8 *, f32);

extern void *D_004826E0;

s32 ScriptCmdEffectGetParamFloatVec_32e060(E8 *p0, s32 p1)
{
    f32 out[4];
    u8 loc[32];
    s32 r;
    s32 m;

    if (p1 < 4 || p1 > 6) {
        return 0;
    }
    r = ScriptSlotGetInt_3348b0(p0++);
    if (D_004826E0 == 0) {
        return 0;
    }
    m = GetEffectMgr_2d9040();
    if (m == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(loc, D_004826E0);
    EffectGetParamFloatVec_2e0240(m, loc, r, out);
    ScriptSlotStoreFloatRef_3347d0(p0++, out[0]);
    ScriptSlotStoreFloatRef_3347d0(p0++, out[1]);
    ScriptSlotStoreFloatRef_3347d0(p0++, out[2]);
    if (p1 > 4) {
        ScriptSlotStoreFloatRef_3347d0(p0, out[3]);
    }
    return 1;
}
