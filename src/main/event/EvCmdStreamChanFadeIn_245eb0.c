#include "types.h"

extern f32 TaggedGetFloat_2490d0(s32);
extern s32 ScriptGetInt_2490f0(s32);
extern void EventVoiceSetChanVolumeFade_24e7d0(s32, f32, s32, s32);
extern void *gEventContext;

s32 EvCmdStreamChanFadeIn_245eb0(s64 *arg0, s32 arg1)
{
    f32 f;
    s32 a;
    s32 b;
    s32 t16;

    t16 = *(s32 *)((u8 *)gEventContext + 4) + 0x420;
    a = ScriptGetInt_2490f0((s32)arg0++);
    b = ScriptGetInt_2490f0((s32)arg0++);
    f = 1.0f;
    if (arg1 >= 3) {
        f = TaggedGetFloat_2490d0((s32)arg0);
    }
    EventVoiceSetChanVolumeFade_24e7d0(t16, f, a, b);
    return 1;
}
