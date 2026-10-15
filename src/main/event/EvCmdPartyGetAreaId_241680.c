#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 ScriptSetRefInt_249030(s32, s32);

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
    u8 pad000[0x4];
    s16 m04;
};

s32 EvCmdPartyGetAreaId_241680(s32 p0, s32 p1)
{
    s32 rv2;
    struct Obj0 *r0;
    struct Obj1 * t0;
    s16 t1;
    s32 r1;

    rv2 = 1;
    if (p1 != 1) {
        rv2 = 0;
    } else {
        r0 = GetGameData_1fede0();
        t0 = r0->m18;
        t1 = r0->m18->m04;
        r1 = ScriptSetRefInt_249030(p0, t1);
        rv2 = 1;
    }
    return rv2;
}
