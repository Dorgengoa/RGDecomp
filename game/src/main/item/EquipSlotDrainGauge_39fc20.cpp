#include "types.h"

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fC0() { return VCM0(s32, 0xC0); }
};

class VA0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    VB * f40() { return VCM0(VB *, 0x40); }
};

class VA : public VA0 {
public:
    u8 pad4[0xC];
    f32 m10;
};

extern "C" f32 EquipSlotGetGaugeDrainRate_3a0290(VA *);
extern "C" u8 *D_00483748;
extern "C" u8 *D_00483754;

extern "C" s32 EquipSlotDrainGauge_39fc20(VA *arg0, f32 fparg0) {
    VB *b;
    f32 v;
    f32 t;

    if (D_00483748 == NULL) {
        return 0;
    }
    if (!(*(u8 *)(*(u8 **)(D_00483748 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    b = arg0->f40();
    if ((b != NULL) && (b->fC0() != 0)) {
        return 0;
    }
    if (!(arg0->m10 <= 0.0f) && (((u64) ((s64) (*(u8 *)(D_00483754 + 0x24C)) << 0x3B) >> 0x3F) == 0)) {
        t = fparg0 * EquipSlotGetGaugeDrainRate_3a0290(arg0);
        arg0->m10 -= t;
        if (arg0->m10 < 0.0f) {
            arg0->m10 = 0.0f;
        }
    }
    return 1;
}
