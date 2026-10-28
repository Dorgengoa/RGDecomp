#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v74(s32 a0) { return VCM(s32, (void *, s32), 0x130, a0); }
};

extern "C" s32 InsectItemCreateWithRandomName_3cff30(s32, s32);
extern "C" void CageRecClearCatch_3d0960(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004838E8;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x6];
    s32 m0C;
};

extern "C" s32 InsectItemCreateFromCageCatch_3cfea0(s32 p0, struct Obj0 *p1)
{
    s32 r0;

    if (D_004838E8 == 0) {
        return 0;
    }
    if (p1 == 0) {
        return 0;
    }
    r0 = InsectItemCreateWithRandomName_3cff30(p0, p1->m18->m04);
    if (r0 == 0) {
        return 0;
    }
    ((struct C0 *)r0)->v74(p1->m18->m0C);
    CageRecClearCatch_3d0960(p1);
    return r0;
}
