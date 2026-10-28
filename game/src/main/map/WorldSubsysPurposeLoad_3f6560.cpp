/* rgp:protos */
#line 1
#include "types.h"

struct Obj003f6560 {
    VC_VPTR_MEMBER;
    
    
    
    
    s32 v5(s32 arg1, s32 arg2, s32 arg3) { return VCM(s32, (void *, s32, s32, s32), 0x1C, arg1, arg2, arg3); }
    s32 v6(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

typedef struct Arg0_003f6560 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    Obj003f6560 *unkC;
    Obj003f6560 *unk10;
    Obj003f6560 *unk14;
    Obj003f6560 *unk18;
} Arg0_003f6560;

extern "C" s32 D_00465880;

extern "C" s32 WorldSubsysPurposeLoad_3f6560(Arg0_003f6560 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Obj003f6560 *temp_4;
    Obj003f6560 *temp_4_2;
    Obj003f6560 *temp_4_3;
    Obj003f6560 *temp_4_4;

    if (arg1 == 0) {
        return 0;
    }
    if (arg0->unk0 == 0) {
        return 0;
    }
    {
        arg0->unk8 = arg3;
        temp_4 = arg0->unkC;
        if (temp_4 != NULL) {
            temp_4->v6((int)(long)(arg1), (int)(long)(arg2), (int)(long)(arg3));
        }
        temp_4_2 = arg0->unk10;
        if (temp_4_2 != NULL) {
            temp_4_2->v5(arg1, D_00465880 != 0, 0);
        }
        temp_4_3 = arg0->unk14;
        if (temp_4_3 != NULL) {
            temp_4_3->v6();
        }
        temp_4_4 = arg0->unk18;
        if (temp_4_4 != NULL) {
            temp_4_4->v6();
        }
        return 1;
    }
}
