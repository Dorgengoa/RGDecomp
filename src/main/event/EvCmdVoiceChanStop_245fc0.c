#include "types.h"

typedef struct Ctx { u8 pad0[0x4]; u8 *f04; } Ctx;
typedef struct A A;

extern Ctx *gEventContext;
extern s32 ScriptGetInt_2490f0(A *a);
extern void EventVoiceFindChanAndStop_24e910(void *p, s32 v);

s32 EvCmdVoiceChanStop_245fc0(A *a)
{
    void *p = gEventContext->f04 + 0x420;
    EventVoiceFindChanAndStop_24e910(p, ScriptGetInt_2490f0(a));
    return 1;
}
