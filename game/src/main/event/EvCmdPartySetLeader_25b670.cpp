#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v13() { return VCM0(s32, 0x3C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v59(s32 a0) { return VCM(s32, (void *, s32), 0xF4, a0); }
};

extern "C" void * GetGameData_1fede0(void);
extern "C" s32 ScriptGetInt_26a2a0(s32);
extern "C" s32 PartySetLeader_3c1600(s32, s32, s32);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);

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

extern "C" s32 EvCmdPartySetLeader_25b670(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;
    s32 t1;
    s32 r3;
    s32 rv7;
    s32 r4;

    if (p1 != 1) {
        return 0;
    }
    r0 = (struct Obj0 *)GetGameData_1fede0();
    r1 = ScriptGetInt_26a2a0(p0);
    t0 = r0->m18;
    r2 = PartySetLeader_3c1600(t0, r1, 0);
    t1 = r0->m14;
    r3 = CharaMgrPoolFindById_3a8c60(t1, r1);
    rv7 = 1;
    if (r3 == 0) {
        rv7 = 0;
    } else {
        r4 = ((struct C0 *)r3)->v46();
        if (r4 != 0) {
            ((struct C0 *)r3)->v59(1);
            ((struct C0 *)r3)->v13();
        }
        rv7 = 1;
    }
    return rv7;
}
