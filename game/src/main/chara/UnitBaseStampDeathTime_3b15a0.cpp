/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v104(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }
};

extern "C" s32 DoubleToUInt_13bb78(double);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj1 * D_00483818;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x198];
    s32 m198;
};

struct Obj1 {
    u8 pad000[0x20];
    struct Obj2 *m20;
};

struct Obj2 {
    u8 pad000[0x238];
    struct Obj3 *m238;
};

struct Obj3 {
    u8 pad000[0x178];
    s64 m178;
};

extern "C" s32 UnitBaseStampDeathTime_3b15a0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct Obj1 * t0;
    s32 r0;
    s32 rv5;
    s32 t1;
    s32 rv4;
    struct Obj1 * t2;
    struct Obj2 * t3;
    struct Obj3 * t4;
    s32 rv3;
    s64 t5;
    s32 r2;

    t0 = D_00483818;
    if (t0 == 0) {
        return 0;
    }
    r0 = ((struct C0 *)p0)->v46((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 == 0) {
        rv5 = 0;
    } else {
        t1 = p0->m198;
        rv4 = 1;
        if (t1 > 0) {
            rv4 = 0;
        } else {
            ((struct C0 *)p0)->v104(1, 1, 1);
            t4 = D_00483818->m20->m238;
            if (t4 != 0) {
                rv3 = DoubleToUInt_13bb78(__builtin_bit_cast(double, (long long)(t4->m178)));
            } else {
                rv3 = 0;
            }
            p0->m198 = rv3;
            rv4 = 1;
        }
        rv5 = rv4;
    }
    return rv5;
}
