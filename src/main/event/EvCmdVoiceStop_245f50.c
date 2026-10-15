#include "types.h"

typedef struct { s32 a, b; } T_00245f50;

extern struct { s32 f0; void *f4; } *gEventContext;
extern s32 ScriptGetInt_2490f0(T_00245f50 *);
extern f32 TaggedGetFloat_2490d0(T_00245f50 *);
extern void EventVoiceStop_24e820(void *, s32, f32);

s32 EvCmdVoiceStop_245f50(T_00245f50 *q)
{
    s32 r;
    void *a;
    f32 f;

    a = (void *)((s32)gEventContext->f4 + 0x420);
    r = ScriptGetInt_2490f0(q++);
    f = TaggedGetFloat_2490d0(q);
    EventVoiceStop_24e820(a, r, f);
    return 1;
}
