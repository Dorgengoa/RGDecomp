/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    s32 v12(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x38, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 ItemInInvCategory0_3d4960(void *);
extern "C" s32 ItemInInvCategory9_3d48e0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x244];
    s16 m244;
};

struct Obj1 {
    u8 pad000[0x4];
    s16 m04;
};

extern "C" s32 CharaSetEquipId244_3acdd0(struct Obj0 *p0, struct Obj1 *p1, int rgp_a2, int rgp_a3)
{
    if (p1 == 0) {
        p0->m244 = -1;
        ((struct C0 *)p0)->v12((int)(long)(p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        return 1;
    }
    if (((unsigned char)ItemInInvCategory0_3d4960(p1)) == 0) {
        if (((unsigned char)ItemInInvCategory9_3d48e0(p1)) == 0) {
            return 0;
        }
    }
    p0->m244 = p1->m04;
    ((struct C0 *)p0)->v12();
    return 1;
}
