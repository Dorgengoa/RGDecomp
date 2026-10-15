#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

extern void * GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetMemberId_3c2490(s32, s32);
extern void ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 EvCmdPartyGetMemberId_260a20(s32 p0, s32 p1)
{
    E8W *q;
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;
    s32 t1;
    s32 r3;

    q = (E8W *)p0;
    r0 = GetGameData_1fede0();
    if (p1 != 2) {
        return 0;
    }
    r1 = ScriptGetInt_26a2a0((s32)q++);
    t0 = r0->m18;
    r2 = PartyCountMembers_3c2010(t0, 1, 1);
    if (r1 < r2) {
        t1 = r0->m18;
        r3 = PartyGetMemberId_3c2490(t1, r1);
        ScriptSetRefInt_26a1e0((s32)q, r3);
    } else {
        ScriptSetRefInt_26a1e0((s32)q, -1);
    }
    return 1;
}
