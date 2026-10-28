/* rgp:protos */
#line 1
#include "types.h"

class VE3B1890 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unkC0(f32 a, int rgp_fwd2 = 0) { return VCM(s32, (void *, int, f32), 0xC0, rgp_fwd2, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    void unkF4(s32 a) { VCM(void, (void *, s32), 0xF4, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unk128(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void call1A4(s32 a0) { VCM(void, (void *, s32), 0x1A4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void call328(s32 a0) { VCM(void, (void *, s32), 0x328, a0); }
    u8 pad4[0x14 - 4];
    s32 unk14;
};

extern "C" s32 CharaRevive_3b1950(VE3B1890 *arg0,s32 arg1, f32 fparg0)
{
    s32 var_5;

    if (arg0->unkC0(fparg0, (int)(long)(arg1)) == 0) {
        return 0;
    }
    arg0->call1A4(1);
    f32 t = (f32) arg0->unk128(1) / 100.0f;
    var_5 = (s32) (t * fparg0);
    if (var_5 <= 0) {
        var_5 = 1;
    }
    arg0->unkF4(var_5);
    arg0->call328(arg1);
    return 1;
}
