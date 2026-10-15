#include "types.h"

struct E8 { s32 a; s32 b; };

extern s32 ScriptGetCodeAddr_249050(struct E8 *);
extern s32 EventCastFindKeyByName_24bb50(s32, s32);
extern s32 ScriptGetInt_2490f0(struct E8 *);
extern void EventCastObjPlayMotion_24b020(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EvCmdCastPlayMotion_247be0(struct E8 *p0, s32 p1)
{
    s32 r3;
    s32 rv4;
    s32 r2;
    s32 r1;
    s32 r0;
    s32 base;
    s32 t1;
    struct Obj0 *t0;
    struct E8 *q;

    q = p0;
    t0 = gEventContext;
    t1 = t0->m04;
    base = t1 + 0x60;
    r0 = ScriptGetCodeAddr_249050(q++);
    r1 = EventCastFindKeyByName_24bb50(base, r0);
    r2 = ScriptGetCodeAddr_249050(q++);
    rv4 = 6;
    if (p1 >= 3) {
        r3 = ScriptGetInt_2490f0(q);
        rv4 = r3;
    }
    EventCastObjPlayMotion_24b020(base, r1, r2, rv4);
    return 1;
}
