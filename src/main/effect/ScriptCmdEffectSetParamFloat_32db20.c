#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern f32 ScriptSlotGetFloat_334890(E8 *);
extern s32 ScriptSlotGetInt_3348b0(E8 *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(void *, void *);
extern void EffectSetParamFloat_2e0600(s32, void *, s32, f32);

extern void *D_004826E0;

s32 ScriptCmdEffectSetParamFloat_32db20(E8 *p0, s32 p1)
{
    u8 loc[32];
    void *o;
    f32 t;
    s32 r;
    s32 m;

    if (p1 != 2 && p1 != 3) {
        return 0;
    }
    o = 0;
    switch (p1) {
    case 2:
        o = D_004826E0;
        break;
    case 3:
        o = D_004826E0;
        break;
    }
    if (o == 0) {
        return 0;
    }
    t = ScriptSlotGetFloat_334890(p0++);
    r = ScriptSlotGetInt_3348b0(p0);
    if (D_004826E0 == 0) {
        return 0;
    }
    m = GetEffectMgr_2d9040();
    if (m == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(loc, D_004826E0);
    EffectSetParamFloat_2e0600(m, loc, r, t);
    return 1;
}
