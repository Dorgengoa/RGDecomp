/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v108(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x1B8, a0, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x12];
    s16 m12;
    u8 pad014[0x13];
    s8 m27;
};

struct Obj2 {
    s32 m00;
};

struct Obj3 {
    s32 m00;
};

extern "C" s32 InsectItemAddExp_3d15f0(struct Obj0 *p0, s32 p1, struct Obj2 *p2, struct Obj3 *p3)
{ s32 rgp_v0;
    struct Obj1 * t0;
    s8 t1;
    struct Obj1 * t2;
    s16 t3;
    struct Obj1 * t4;
    s8 t5;

    if (p2 != 0) {
        t0 = p0->m18;
        t1 = p0->m18->m27;
        p2->m00 = t1;
    }
    t2 = p0->m18;
    t3 = p0->m18->m12;
    rgp_v0 = ((struct C0 *)p0)->v108(t3 + p1, (int)(long)(p2), (int)(long)(p3));
    if (p3 != 0) {
        t4 = p0->m18;
        t5 = p0->m18->m27;
        p3->m00 = t5;
        return rgp_v0;
    }
return rgp_v0; }
