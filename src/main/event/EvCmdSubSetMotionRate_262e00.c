#include "types.h"

struct E { s32 a; s32 b; };

extern s32 ScriptGetInt_26a2a0(void *p);
extern f32 TaggedGetFloat_26a280(void *p);
extern s32 EvtGetSubMachine_26abb0(s32 a);
extern void EventSubNodeAddSetMotionRate_2511b0(s32 r, f32 x);

s32 EvCmdSubSetMotionRate_262e00(struct E * p0)
{
    s32 a;
    f32 x;
    s32 r;

    a = ScriptGetInt_26a2a0(p0++);
    x = TaggedGetFloat_26a280(p0);

    r = EvtGetSubMachine_26abb0(a);
    if (r == 0) {
        return 0;
    }
    EventSubNodeAddSetMotionRate_2511b0(r, x);
    return 1;
}
