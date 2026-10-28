/* rgp:protos */
#line 1
#include "types.h"

/* THREE edits, all needed:
   (1) `jalr $25` = C++ virtual, vptr +0, slot 0x50 = virtual #18
       ([[levers.d/jalr-is-cpp-virtual]]);
   (2) the f32 at +0x10 must be a real class MEMBER -- as
       `*(f32 *)((u8 *)self + 0x10)` mwcc CSEs the address into `$v0` and
       addresses it as `0($v0)` (+1 word, 4 wrong words);
   (3) the virtual's result must be named in a LOCAL and tested with an EARLY
       return: `r = self->v18(); if (r == 0) return 0;`. Calling it inside the
       guard, or naming it and keeping the block form, is 33 words -- retail
       annuls `daddu $4,$17,$0` (the next call's argument) in the `bnezl`
       slot and only that spelling leaves it sinkable. */

class VE39FFA0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v18(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x50, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad004[0x10 - 4];
    f32 f10;
};
extern "C" s32 EquipSlotGetGaugeMax_3a02d0(VE39FFA0 *);

extern "C" s32 EquipSlotSetGaugeClamped_39ffa0(VE39FFA0 *self, s32 arg1, int rgp_a2, int rgp_a3)
{
    f32 t;
    s32 r;

    r = self->v18((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r == 0) { return 0; }
    t = (f32)EquipSlotGetGaugeMax_3a02d0(self);
    if (arg1 < 0) {
        self->f10 = t;
    } else {
        self->f10 = (f32)arg1;
    }
    if (!(self->f10 <= t)) {
        self->f10 = t;
    }
    return 1;
}
