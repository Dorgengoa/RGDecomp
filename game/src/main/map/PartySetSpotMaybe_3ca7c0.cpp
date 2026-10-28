/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern u8 D_00465940[0x400];
extern void *D_00483894;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s64 x0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s64, int, int), 0x70, x0, rgp_fwd2, rgp_fwd3); }
};
typedef struct {
    u8 pad0[0x8];
    s16 unk8;
    u8 padA[0x12];
    s32 unk1C;
    u8 pad20[0xf8];
    s64 unk118;
    s32 unk120;
    s32 unk124;
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    u32 unk138;
    s16 unk13C;
    u8 pad13E[0x2];
    s32 unk140;
    u8 pad144[0xc];
    s32 unk150;
    s32 unk154;
    s32 unk158;
    s32 unk15C;
} T3ca7c0_arg0;

s32 PartySetSpotMaybe_3ca7c0(T3ca7c0_arg0 *arg0, s64 arg1, int rgp_a2, int rgp_a3)
{
    s32 temp_2;
    void *self;
    void *vtbl;

    if (D_00483894 == NULL) {
        return 0;
    }
    self = *(void **)((u8 *)D_00483894 + 0x34);
    self = *(void **)((u8 *)self + 0xC);
    vtbl = *(void **)self;
    temp_2 = ((VC_0 *)(self))->f((s64)(s16)arg1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (temp_2 == 0) {
        return 0;
    }
    if (arg0->unk8 == arg1) {
        return 1;
    }
    arg0->unk8 = (s16)arg1;
    arg0->unk1C = temp_2;
    arg0->unk118 = 0;
    arg0->unk120 = 0;
    arg0->unk124 = 0;
    {
        f32 t = (*(f32 *)D_00465940);
        arg0->unk128 = t;
        arg0->unk12C = t;
        arg0->unk130 = t;
        arg0->unk134 = t;
    }
    arg0->unk138 = 0x41300000;
    arg0->unk13C = 0;
    arg0->unk140 = 0;
    arg0->unk150 = 0;
    arg0->unk154 = 0;
    arg0->unk158 = 0;
    arg0->unk15C = 0;
    return 1;
}

}
