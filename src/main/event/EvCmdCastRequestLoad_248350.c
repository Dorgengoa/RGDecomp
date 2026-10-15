#include "types.h"

/* lane N4 family: EvCmdCastRequestLoad_248170 / 00248200 / 00248240 / 002482d0 /
   00248310 / 00248350 - six byte-identical 56 B thunks, one source text. */

struct Obj0 { u8 pad00[4]; u8 *m04; };

extern struct Obj0 *gEventContext;

extern s32 ScriptGetCodeAddr_249050(void);
extern void EventCastRequestLoad_24bc30(u8 *, s32);

void EvCmdCastRequestLoad_248350(void)
{
    u8 *q;

    q = gEventContext->m04 + 0x60;
    EventCastRequestLoad_24bc30(q, ScriptGetCodeAddr_249050());
}
