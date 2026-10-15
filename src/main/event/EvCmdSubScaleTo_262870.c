#include "types.h"

extern void EventSubNodeAddScaleTo_250ec0(s32, f32 *, s32);
extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 EvtGetSubMachine_26abb0(s32);


s32 EvCmdSubScaleTo_262870(s64 *arg0, s32 arg1)
{
    f32 v[4];
    s32 a;
    s32 x;
    s32 r;
    s32 i;

    x = 0;
    a = ScriptGetInt_26a2a0((s32)arg0++);
    v[0] = TaggedGetFloat_26a280((s32)arg0++);
    v[1] = TaggedGetFloat_26a280((s32)arg0++);
    v[2] = TaggedGetFloat_26a280((s32)arg0++);
    v[3] = 1.0f;
    if (arg1 >= 5) {
        x = ScriptGetInt_26a2a0((s32)arg0);
    }
    r = EvtGetSubMachine_26abb0(a);
    if (r == 0) {
        return 0;
    }
    EventSubNodeAddScaleTo_250ec0(r, v, x);
    return 1;
}
