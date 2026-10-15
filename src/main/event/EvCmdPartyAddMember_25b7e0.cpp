#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
};

extern "C" void * GetGameData_1fede0(void);
extern "C" s32 ScriptGetInt_26a2a0(s32);
extern "C" s32 PartyAddMember_3c1430(s32, s32, s32);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" void PartyCharaEquipDefaultsMaybe_3c1250(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    s32 m18;
};

extern "C" s32 EvCmdPartyAddMember_25b7e0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;
    s32 rv7;
    s32 t1;
    s32 r3;
    s32 rv6;
    s32 t2;

    if (p1 != 1) {
        return 0;
    }
    r0 = (struct Obj0 *)GetGameData_1fede0();
    r1 = ScriptGetInt_26a2a0(p0);
    t0 = r0->m18;
    r2 = PartyAddMember_3c1430(t0, r1, 0);
    if (r2 == 0) {
        rv7 = 0;
    } else {
        t1 = r0->m14;
        r3 = CharaMgrPoolFindById_3a8c60(t1, r1);
        rv6 = 1;
        if (r3 == 0) {
            rv6 = 0;
        } else {
            t2 = r0->m18;
            PartyCharaEquipDefaultsMaybe_3c1250(t2, r1);
            ((struct C0 *)r3)->v12();
            rv6 = 1;
        }
        rv7 = rv6;
    }
    return rv7;
}
