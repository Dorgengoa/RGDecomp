/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v110(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x1C0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 CharaSysEventLogRecordOpenHud_3a3260(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_00483818;

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

extern "C" s32 CharaRollInstantKillLogged_3b20a0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;
    struct Obj0 * t0;
    s32 t1;
    s32 r1;

    r0 = ((struct C0 *)p0)->v110((int)(long)(p1), (int)(long)(p2), (int)(long)(p3));
    if ((r0 & 0xFF) != 0) {
        t0 = D_00483818;
        t1 = D_00483818->m20;
        r1 = CharaSysEventLogRecordOpenHud_3a3260(t1, p3, p4, 0xA, 0xC);
        return (r0 & 0xFF);
    }
    return (r0 & 0xFF);
}
