#include "types.h"

extern s32 ScriptGetCodeAddr_249050(s32 arg0);
extern s32 ScriptGetInt_2490f0(s32 arg0);
extern void EventCastObjClothReset_24a420(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 EventCastFindKeyByName_24bb50(s32 arg0, s32 arg1);
extern void *gEventContext;

s32 EvCmdCastClothReset_247380(s64 *arg0, s32 arg1)
{
    s32 t;
    s32 a;
    s32 b;
    s32 base;

    base = *(s32 *)((u8 *)gEventContext + 0x4) + 0x60;
    t = EventCastFindKeyByName_24bb50(base, ScriptGetCodeAddr_249050((s32)arg0++));
    a = 0x1E;
    b = 0;
    if (arg1 >= 2) {
        a = ScriptGetInt_2490f0((s32)arg0++);
    }
    if (arg1 >= 3) {
        b = ScriptGetInt_2490f0((s32)arg0) != 0;
    }
    EventCastObjClothReset_24a420(base, t, a, b);
    return 1;
}
