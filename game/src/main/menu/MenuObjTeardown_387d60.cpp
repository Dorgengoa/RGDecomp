/* rgp:protos */
#line 1
#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20() { return VCM0(s32, 0x58); }
};

extern "C" s32 GetDrawCtxNameTable_15de40(void);
extern "C" void NameTableFreeGroup_158ac0(s32, s32);
extern "C" void MenuObjReset_387dc0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4DC];
    s32 m4DC;
    u8 pad4E0[0x4A5];
    s8 m985;
};

extern "C" void MenuObjTeardown_387d60(struct Obj0 *p0)
{
    s8 t0;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 r2;
    s32 r3;

    t0 = p0->m985;
    if (t0 != 0) {
        r0 = GetDrawCtxNameTable_15de40();
        t1 = p0->m4DC;
        r1 = (NameTableFreeGroup_158ac0(r0, t1), (s32)0);
        r2 = ((struct C432 *)p0)->v20();
        r3 = (MenuObjReset_387dc0(p0), (s32)0);
        return;
    }
}
