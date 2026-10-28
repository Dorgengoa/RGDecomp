#include "types.h"
class V003C98B0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    void x14() { VCM0(void, 0x40); }
    
    
    
    
    
    
    
    
    
    
    
    s32 f26(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};
struct B003C98B0 {
    u8 pad0[0x14];
    V003C98B0 *unk14;
};

struct A003C98B0 {
    u8 pad0[0x34];
    B003C98B0 *unk34;
};

struct O003C98B0 {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[0x1A4 - 6];
    u8 b0 : 1;
    u8 b1 : 7;
    u8 pad1A5;
    s16 unk1A6;
    s16 unk1A8;
    u8 pad1AA[2];
    f32 unk1AC;
    f32 unk1B0;
};

extern "C" {
extern s32 D_004659D8[];
extern A003C98B0 *D_00483894;
}

extern "C" s32 PartyPendingWarpSet_3c98b0(O003C98B0 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4)
{
    f32 f;

    if (D_00483894 == 0) {
        return 0;
    }
    arg0->b0 = 0;
    arg0->unk1A6 = -1;
    arg0->unk1A8 = -1;
    arg0->unk1AC = 0.0f;
    arg0->unk1B0 = 0.0f;
    if (D_00483894->unk34->unk14->f26(arg1) == 0) {
        return 0;
    }
    if (arg2 < 0) {
        arg2 = arg0->unk4;
    }
    arg0->b0 = 1;
    arg0->unk1A6 = arg2;
    arg0->unk1A8 = arg1;
    f = D_004659D8[0];
    arg0->unk1AC = f;
    arg0->unk1B0 = f;
    if (arg3 > 0.0f) {
        arg0->unk1AC = arg3;
    }
    if (arg4 > 0.0f) {
        arg0->unk1B0 = arg4;
    }
    return 1;
}
