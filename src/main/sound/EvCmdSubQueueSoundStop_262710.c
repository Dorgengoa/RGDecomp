/* EvCmdSubQueueSoundStop_262710 -- shape-identical to merged EvCmdMenuWinSetSize_264f40 (30 instructions); the donor's
   source with the symbol renamed and 2 call target(s) substituted:
     MenuWinGet_2653e0 -> EvtGetSubMachine_26abb0
     MenuWinSetSize_26c320 -> EventSubNodeAddStopSound_250db0
   Found by build/zz/s23_xclone.py. */
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern s32 ScriptGetInt_26a2a0(s32);
extern void *EvtGetSubMachine_26abb0(s32);
extern void EventSubNodeAddStopSound_250db0(void *, s32, s32);

s32 EvCmdSubQueueSoundStop_262710(Cmd *p0)
{
    s32 id, a, b;
    void *h;

    id = ScriptGetInt_26a2a0((s32)p0++);
    a = ScriptGetInt_26a2a0((s32)p0++);
    b = ScriptGetInt_26a2a0((s32)p0);
    h = EvtGetSubMachine_26abb0(id);
    if (h == 0) {
        return 0;
    }
    EventSubNodeAddStopSound_250db0(h, a, b);
    return 1;
}
