#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 EventSceneGetObj_2676e0(s32);
extern s32 EventCastSlotSetAt_258e10(void *, s32, s32, s32, s32);
extern u8 D_004BDDB0[0x400];

s32 EvCmdCastSlotBind_261770(s64 *arg0)
{
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetInt_26a2a0((s32)arg0);
    c = EventSceneGetObj_2676e0(b);
    if (c != 0) {
        return EventCastSlotSetAt_258e10(&(*(u8 *)D_004BDDB0), a, 0, b, c);
    }
    return 0;
    return EventCastSlotSetAt_258e10(&(*(u8 *)D_004BDDB0), a, 0, b, c);
}
