#include "types.h"

extern s32 ScriptGetInt_2490f0(s32);
extern s32 MesWinSetFrameType_272b30(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x42C];
    s32 m42C;
};

s32 EvCmdEventMesWinSetFrameType_245a30(s32 p0)
{
    struct Obj0 * t0;
    struct Obj1 * t1;
    s32 t2;
    s32 rv2;
    s32 r0;
    s32 r1;

    t0 = gEventContext;
    t1 = gEventContext->m04;
    t2 = gEventContext->m04->m42C;
    rv2 = 1;
    if (t2 == 0) {
        rv2 = 0;
    } else {
        r0 = ScriptGetInt_2490f0(p0);
        r1 = MesWinSetFrameType_272b30(t2, r0);
        rv2 = 1;
    }
    return rv2;
}
