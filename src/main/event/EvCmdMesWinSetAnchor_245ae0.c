#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj2 {
    u8 pad000[0x48];
    f32 m48;
    f32 m4C;
};

struct Obj1 {
    u8 pad000[0x42C];
    struct Obj2 *m42C;
};

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

extern struct Obj0 * gEventContext;
extern f32 TaggedGetFloat_2490d0(E8 *);
extern s32 ScriptGetInt_2490f0(E8 *);
extern struct Obj2 * MesMgrGetSlotWin_24fcc0(s32);

s32 EvCmdMesWinSetAnchor_245ae0(E8 *p0, s32 p1)
{
    struct Obj2 *t;
    s32 r0;

    if (p1 == 2) {
        t = gEventContext->m04->m42C;
        if (t == 0) {
            return 0;
        }
        t->m48 = TaggedGetFloat_2490d0(p0++);
        t->m4C = TaggedGetFloat_2490d0(p0);
    } else if (p1 == 3) {
        r0 = ScriptGetInt_2490f0(p0++);
        t = MesMgrGetSlotWin_24fcc0(r0);
        if (t == 0) {
            return 0;
        }
        t->m48 = TaggedGetFloat_2490d0(p0++);
        t->m4C = TaggedGetFloat_2490d0(p0);
    }
    return 1;
}
