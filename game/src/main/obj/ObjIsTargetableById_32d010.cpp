#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v58() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v137() { return VCM0(s32, 0x22C); }
};

extern "C" void * GetGameData_1fede0(void);
extern "C" s32 ObjFindById_3bb3a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    s32 m1C;
};

extern "C" s32 ObjIsTargetableById_32d010(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    t0 = r0->m1C;
    r1 = ObjFindById_3bb3a0(t0, p0);
    if (r1 == 0) {
        goto zero;
    }
    r2 = ((struct C0 *)r1)->v58();
    if (r2 == 0) {
        goto zero;
    }
    r3 = ((struct C0 *)r1)->v137();
    if ((r3 & 0xFF) != 0) {
        goto one;
    }
zero:
    return 0;
one:
    return 1;
}
