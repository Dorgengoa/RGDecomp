#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptSlotGetInt_3348b0(E8 *);
extern f32 ScriptSlotGetFloat_334890(E8 *);
extern s32 GetCurrentScene_1f5be0(void);
extern void GameSceneSoundSlot5PlaySeVol_1d05d0(s32, s32, f32);

s32 ScriptCmdSoundChanPlay_32d150(E8 *p0, s32 p1)
{
    s32 a;
    f32 t;
    s32 r;

    if (p1 <= 0) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0(p0);
    t = 1.0f;
    if (p1 > 1) {
        t = ScriptSlotGetFloat_334890(p0 + 1);
    }
    r = GetCurrentScene_1f5be0();
    GameSceneSoundSlot5PlaySeVol_1d05d0(r, a, t);
    return 1;
}
