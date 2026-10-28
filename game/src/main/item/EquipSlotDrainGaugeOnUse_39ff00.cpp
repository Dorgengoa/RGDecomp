/* rgp:protos */
#line 1
#include "types.h"

class V39ff00 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 alive(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x50, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad4[0xC];
    f32 unk10;
};

typedef struct { u8 pad[0x24C]; u8 lo:4; u8 b4:1; } H39ff00;
typedef struct { u8 pad[0x20]; H39ff00 *h; } G39ff00;

extern "C" {
extern s32 EquipSlotGetGaugeUseCost_3a0260(V39ff00 *);
extern G39ff00 *D_00483748;
}

extern "C" s32 EquipSlotDrainGaugeOnUse_39ff00(V39ff00 *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    f32 t;

    if (self->alive((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    if (self->unk10 <= 0.0f) {
        return 0;
    }
    if (D_00483748->h->b4) {
        return 0;
    }
    t = self->unk10 - (f32)EquipSlotGetGaugeUseCost_3a0260(self);
    self->unk10 = t;
    return (s32)t;
}
