#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptGetInt_26a2a0(E8 *);
extern f32 TaggedGetFloat_26a280(E8 *);
extern s32 EvtGetSubMachine_26abb0(s32);
extern void EventSubNodeAddWinColorTo_250f60(s32, f32 *, s32);

s32 EvCmdSubWinColorTo_262990(E8 *p0, s32 p1)
{
    f32 v[4];
    s32 r0;
    s32 h;
    s32 x;

    h = 0;
    r0 = ScriptGetInt_26a2a0(p0++);
    v[0] = TaggedGetFloat_26a280(p0++);
    v[1] = TaggedGetFloat_26a280(p0++);
    v[2] = TaggedGetFloat_26a280(p0++);
    v[3] = TaggedGetFloat_26a280(p0++);
    if (p1 >= 6) {
        h = ScriptGetInt_26a2a0(p0);
    }
    x = EvtGetSubMachine_26abb0(r0);
    if (x == 0) {
        return 0;
    }
    EventSubNodeAddWinColorTo_250f60(x, v, h);
    return 1;
}
