#include "types.h"

typedef struct Ctx { u8 pad0[0x4]; u8 *f04; } Ctx;
typedef struct A A;

extern Ctx *gEventContext;
extern s32 ScriptGetCodeAddr_249050(A *a);
extern void EventCastFindKeyByName_24bb50(void *p, s32 v);

s32 EvCmdCastFindKey_2478b0(A *a)
{
    void *p = gEventContext->f04 + 0x60;
    EventCastFindKeyByName_24bb50(p, ScriptGetCodeAddr_249050(a));
    return 1;
}
