/* rgp:protos */
#define RGP_SELF_EvCmdSubQueueSoundPlay_262790 1
#include "port/game_protos.h"
#line 1
/* EvCmdSubQueueSoundPlay_262790 -- shape-identical to merged EvCmdMenuWinSetSize_264f40 (30 instructions); the donor's
   source with the symbol renamed and 2 call target(s) substituted:
     MenuWinGet_2653e0 -> EvtGetSubMachine_26abb0
     MenuWinSetSize_26c320 -> EventSubNodeAddPlaySound_250e30
   Found by build/zz/s23_xclone.py. */
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSubQueueSoundPlay_262790(Cmd *p0)
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
    EventSubNodeAddPlaySound_250e30(h, a, b);
    return 1;
}
