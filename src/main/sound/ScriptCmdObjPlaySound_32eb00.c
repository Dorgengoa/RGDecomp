#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 ScriptSlotGetInt_3348b0(void *);
extern f32 ScriptSlotGetFloat_334890(void *);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);

s32 ScriptCmdObjPlaySound_32eb00(void *a0, s32 mode)
{
    s32 v;
    s32 r;
    s32 rec;
    s32 t;
    f32 f;

    if (mode != 2 && mode != 3) {
        return 0;
    }
    v = GetCurrentScene_1f5be0();
    r = ScriptSlotGetInt_3348b0(a0);
    rec = ObjRecGetLiveObject_1c4a90(v, r);
    if (rec == 0) {
        return 1;
    }
    f = 1.0f;
    if (mode > 2) {
        f = ScriptSlotGetFloat_334890((u8 *)a0 + 0x10);
    }
    t = *(s32 *)(rec + 0x4FC);
    SoundPlayScaledVolume_1b9520(t, ScriptSlotGetInt_3348b0((u8 *)a0 + 8), 0, f);
    return 1;
}
