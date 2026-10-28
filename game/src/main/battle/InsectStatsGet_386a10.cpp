/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v76() { return VCM0(s32, 0x138); }
    s32 v77() { return VCM0(s32, 0x13C); }
    
    
    
    
    
    s32 v83() { return VCM0(s32, 0x154); }
    s32 v84(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x158, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    s32 v90() { return VCM0(s32, 0x170); }
    
    
    s32 v93() { return VCM0(s32, 0x17C); }
    
    
    s32 v96(s32 arg1) { return VCM(s32, (void *, s32), 0x188, arg1); }
};

typedef struct Arg0Struct {
    u8 pad0[0x96C];
    C0 *unk96C;
} Arg0Struct;

typedef struct Arg1Struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18[6];
} Arg1Struct;

extern "C" void InsectStatsGet_386a10(Arg0Struct *arg0, Arg1Struct *arg1, int rgp_a2, int rgp_a3) {
    s32 temp_2;
    C0 *temp_17;
    s32 var_16;

    if (arg1 != NULL) {
        temp_17 = arg0->unk96C;
        if (temp_17 != NULL) {
            arg1->unk0 = temp_17->v84((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
            arg1->unk4 = temp_17->v83();
            arg1->unk8 = temp_17->v77();
            arg1->unkC = temp_17->v76();
            arg1->unk10 = temp_17->v90();
            arg1->unk14 = temp_17->v93();
            var_16 = 0;
            do {
                temp_2 = temp_17->v96(var_16);
                arg1->unk18[var_16] = temp_2;
                var_16 += 1;
            } while (var_16 < 6);
        }
    }
}
