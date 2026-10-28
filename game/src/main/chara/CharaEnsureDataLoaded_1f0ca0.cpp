#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
};

extern "C" void * GetGameData_1fede0(void);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" s32 CharaDataEnsureLoaded_1f0d00(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
};

extern "C" s32 CharaEnsureDataLoaded_1f0ca0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    t0 = r0->m14;
    r1 = CharaMgrPoolFindById_3a8c60(t0, p1);
    if (r1 != 0) {
        r2 = ((struct C0 *)r1)->v21();
        r3 = CharaDataEnsureLoaded_1f0d00(p0, r2);
        return r3;
    }
    return 0;
}
