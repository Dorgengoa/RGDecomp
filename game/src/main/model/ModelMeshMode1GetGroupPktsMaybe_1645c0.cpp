/* rgp:protos */
#line 1
#include "types.h"

struct C80 {
    u8 pad000[0x50];
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 v6(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0xA8];
    s32 mA8;
    u8 pad0AC[0x14];
    s32 mC0;
};

struct Obj1 {
    s32 m00;
    s32 m04;
};

struct Obj2 {
    s32 m00;
};

extern "C" s32 ModelMeshMode1GetGroupPktsMaybe_1645c0(struct Obj0 *p0, s32 p1, struct Obj1 *p2, struct Obj2 *p3)
{ s32 rgp_v0;
    s32 t0;
    s32 t1;

    rgp_v0 = ((struct C80 *)p0)->v6((int)(long)(p1), (int)(long)(p2), (int)(long)(p3));
    t0 = p0->mA8;
    p2->m00 = t0;
    t1 = p0->mC0;
    p3->m00 = t1;
    p2->m04 = -1;
return rgp_v0; }
