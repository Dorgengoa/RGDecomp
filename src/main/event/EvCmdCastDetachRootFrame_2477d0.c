#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

extern s32 ScriptGetCodeAddr_249050(s32);
extern s32 EventCastFindKeyByName_24bb50(s32, s32);
extern s32 EventCastObjDetachRootFrame_24ab90(s32, s32);

extern struct Obj0 * gEventContext;

s32 EvCmdCastDetachRootFrame_2477d0(s32 p0)
{
    s32 t1;
    s32 q;
    s32 r0;
    s32 r1;
    s32 r2;

    t1 = gEventContext->m04;
    q = t1 + 0x60;
    r0 = ScriptGetCodeAddr_249050(p0);
    r1 = EventCastFindKeyByName_24bb50(q, r0);
    r2 = EventCastObjDetachRootFrame_24ab90(q, r1);
    return 1;
}
