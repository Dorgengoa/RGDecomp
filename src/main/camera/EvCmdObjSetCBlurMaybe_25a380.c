#include "types.h"

extern void GameSceneObjSetCBlurMaybe_1cf900(s32, s32, s32, f32);
extern s32 GetCurrentScene_1f5be0(void);
extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);

s32 EvCmdObjSetCBlurMaybe_25a380(s64 *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 v;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetInt_26a2a0((s32)arg0++);
    v = 1;
    if (arg1 >= 3) {
        v = (s32)TaggedGetFloat_26a280((s32)arg0);
    }
    GameSceneObjSetCBlurMaybe_1cf900(GetCurrentScene_1f5be0(), a, b, (f32)v);
    return 1;
}
