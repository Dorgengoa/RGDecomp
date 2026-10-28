#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20() { return VCM0(s32, 0x58); }
    
    
    
    
    
    
    
    
    
    s32 v30() { return VCM0(s32, 0x80); }
    
    
    
    
    
    
    
    
    s32 v39(void * a0) { return VCM(s32, (void *, void *), 0xA4, a0); }
    s32 v40(void * a0) { return VCM(s32, (void *, void *), 0xA8, a0); }
};

extern "C" void * GetCurrentScene_1f5be0(void);
extern "C" s32 ObjRecGetLiveObject_1c3bc0(void *, s32);
extern "C" void VecSub_13be40(void *, void *, void *);
extern "C" void SoundSetListener_1b7fa0(void *, void *);
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
};

extern "C" void SoundSetListenerFromCamera_2f74f0(void)
{
    u128 v30;
    u128 v20;
    struct Obj0 *r0;
    s32 t0;
    s32 r1;

    r0 = (struct Obj0 *)GetCurrentScene_1f5be0();
    t0 = r0->m4344;
    r1 = ObjRecGetLiveObject_1c3bc0(r0, t0);
    ((struct C192 *)r1)->v39(&v30);
    ((struct C192 *)r1)->v40(&v20);
    VecSub_13be40(&v20, &v20, &v30);
    SoundSetListener_1b7fa0(&v30, &v20);
}
