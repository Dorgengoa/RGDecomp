#include "types.h"

/* Known-positive sibling shape of EvCmdTaskSetRenderTasksEnabled_25bc50 (byte-identical, in cunits). */

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 PauseSetAllowed_2f6640(s32);

s32 EvCmdPauseSetAllowed_25c550(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = PauseSetAllowed_2f6640((r0 != 0));
    return 1;
}
