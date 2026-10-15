#include "types.h"

extern void GameSceneSetTint_1ce940(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 ScriptGetInt_2490f0(s32);

extern s32 *gEventContext;

s32 EvCmdSceneSetTint_241760(s64 *arg0, s32 arg1) {
    s32 ctx;
    s32 a;
    s32 b;

    ctx = *gEventContext;
    if (ScriptGetInt_2490f0((s32)arg0++) != 0) {
        if (arg1 == 1) {
            GameSceneSetTint_1ce940(ctx, 1, 0x80, 0x80, 0x80);
        } else {
            a = ScriptGetInt_2490f0((s32)arg0++);
            b = ScriptGetInt_2490f0((s32)arg0++);
            GameSceneSetTint_1ce940(ctx, 1, a, b, ScriptGetInt_2490f0((s32)arg0++));
        }
    } else {
        GameSceneSetTint_1ce940(ctx, 0, 0x80, 0x80, 0x80);
    }
    return 1;
}
