#include "types.h"

class VE3B1890 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unkC0(f32 a) { return VCM(s32, (void *, f32), 0xC0, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    void unkF4(s32 a) { VCM(void, (void *, s32), 0xF4, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unk128(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }

    u8 pad4[0x14 - 4];
    s32 unk14;
};

extern "C" s32 CharaHpRaiseToPercent_3b1890(VE3B1890 *arg0, f32 fparg0)
{
    s32 var_5;

    if (arg0->unkC0(fparg0) != 0) {
        return 0;
    }
    f32 t = (f32) arg0->unk128(1) / 100.0f;
    var_5 = (s32) (t * fparg0);
    if (var_5 <= 0) {
        var_5 = 1;
    }
    if ((u32) arg0->unk14 < (u32) var_5) {
        arg0->unkF4(var_5);
    }
    return 1;
}
