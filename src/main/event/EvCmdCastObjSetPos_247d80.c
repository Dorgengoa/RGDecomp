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
extern void TaggedGetVec3_249070(void *, E8 *);
extern void EventCastObjSetPos_24a910(void *, s32, void *);
extern s32 ScriptGetInt_2490f0(E8 *);

s32 EvCmdCastObjSetPos_247d80(E8 *p0, s32 p1)
{
    f32 loc[4];
    s32 a;
    s32 b;
    void *base;
    s32 i1;
    s32 i2;

    base = (void *)((u8 *)gEventContext->m04 + 0x60);
    a = ScriptGetCodeAddr_249050(p0++);
    b = EventCastFindKeyByName_24bb50(base, a);
    if (p1 == 4) {
        TaggedGetVec3_249070(loc, p0);
        p0 += 3;
        EventCastObjSetPos_24a910(base, b, loc);
    }
    if (p1 == 3) {
        i1 = ScriptGetInt_2490f0(p0++);
        i2 = ScriptGetInt_2490f0(p0);
        loc[0] = (f32)i1;
        loc[1] = (f32)i2;
        EventCastObjSetPos_24a910(base, b, loc);
    }
    return 1;
}
