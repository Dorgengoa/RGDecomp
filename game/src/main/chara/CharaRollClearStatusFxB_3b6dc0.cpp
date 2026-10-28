/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v147(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x254, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    s32 v148(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x258, a0, a1); }
};

extern "C" s32 StatusRollChance_3b7050(s32, s32, s32);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" s32 GameSceneSoundSlot5PlaySeVol_1d05d0(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 CharaRollClearStatusFxB_3b6dc0(s32 p0, s32 p1, s32 p2, int rgp_a3)
{
    s32 r0;
    s32 r1;
    s32 rv5;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ((struct C0 *)p0)->v147((int)(long)(p1), (int)(long)(p2), (int)(long)(rgp_a3));
    if (r0 == 0) {
        return 0;
    }
    r1 = StatusRollChance_3b7050(p0, p1, p2);
    rv5 = 1;
    if ((r1 & 0xFF) == 0) {
        rv5 = 0;
    } else {
        r2 = ((struct C0 *)p0)->v148(0, 0);
        r3 = GetCurrentScene_1f5be0();
        r4 = GameSceneSoundSlot5PlaySeVol_1d05d0(r3, 0x49, 1.0f);
        rv5 = 1;
    }
    return rv5;
}
