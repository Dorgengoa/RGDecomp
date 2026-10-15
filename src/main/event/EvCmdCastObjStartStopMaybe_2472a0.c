#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj1 {
    u8 pad000[0x60];
};

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

extern struct Obj0 * gEventContext;
extern s32 ScriptGetCodeAddr_249050(E8 *);
extern s32 EventCastFindKeyByName_24bb50(void *, s32);
extern f32 TaggedGetFloat_2490d0(E8 *);
extern void TaggedGetVec3_249070(void *, E8 *);
extern void EventCastObjStartStopMaybe_24a2b0(void *, s32, f32, void *);

s32 EvCmdCastObjStartStopMaybe_2472a0(E8 *p0, s32 p1)
{
    u8 loc[16];
    s32 a;
    s32 b;
    void *base;
    f32 t;

    base = (void *)((u8 *)gEventContext->m04 + 0x60);
    a = ScriptGetCodeAddr_249050(p0++);
    b = EventCastFindKeyByName_24bb50(base, a);
    switch (p1) {
    case 1:
    case 2:
        t = -1.0f;
        break;
    case 5:
        t = TaggedGetFloat_2490d0(p0++);
        TaggedGetVec3_249070(loc, p0);
        break;
    }
    EventCastObjStartStopMaybe_24a2b0(base, b, t, loc);
    return 1;
}
