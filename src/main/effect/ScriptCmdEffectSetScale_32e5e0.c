#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(void *, s32);
extern void EffectSetScale_2e0ce0(s32, void *, f32 *);
extern f32 ScriptSlotGetFloat_334890(s32);
extern void ScriptSlotGetInt_3348b0(s32);
extern f32 D_0047F550;
extern f32 D_0047F554;
extern f32 D_0047F558;
extern f32 D_0047F55C;
extern s32 D_004826E0;

s32 ScriptCmdEffectSetScale_32e5e0(s64 *arg0, s32 arg1)
{
    f32 v[4];
    u8 buf[0x20];
    f32 x;
    f32 y;
    f32 z;
    s32 h;

    if (arg1 != 4) {
        return 0;
    }

    ScriptSlotGetInt_3348b0((s32)arg0++);
    x = ScriptSlotGetFloat_334890((s32)arg0++);
    y = ScriptSlotGetFloat_334890((s32)arg0++);
    z = ScriptSlotGetFloat_334890((s32)arg0);
    v[0] = D_0047F550;
    v[1] = D_0047F554;
    v[2] = D_0047F558;
    v[3] = D_0047F55C;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    if (D_004826E0 == 0) {
        return 0;
    }
    h = GetEffectMgr_2d9040();
    if (h == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(buf, D_004826E0);
    EffectSetScale_2e0ce0(h, buf, v);
    return 1;
}
