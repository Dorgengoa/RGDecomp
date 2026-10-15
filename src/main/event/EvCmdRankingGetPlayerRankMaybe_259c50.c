#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x4C90];
    s32 m4C90;
};

s32 EvCmdRankingGetPlayerRankMaybe_259c50(s32 p0)
{
    struct Obj0 *r0;
    s32 t1;
    s32 r1;

    r0 = GetGameData_1fede0();
    t1 = r0->m18->m4C90;
    r1 = ScriptSetRefInt_26a1e0(p0, t1);
    return 1;
}
