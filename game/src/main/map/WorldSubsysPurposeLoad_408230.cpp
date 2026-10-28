#include "types.h"

class Obj00408230 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void v1C(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1C, a0, a1, a2); }
    void v20() { VCM0(void, 0x20); }
};

typedef struct Node_00408230 {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    Obj00408230 *unkC;
    Obj00408230 *unk10;
} Node_00408230;

extern "C" {
extern s32 D_00465840;

s32 WorldSubsysPurposeLoad_408230(Node_00408230 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Obj00408230 *temp_4;
    Obj00408230 *temp_4_2;

    if (arg1 == 0) {
        return 0;
    }
    if (arg0->unk0 == 0) {
        return 0;
    }
    arg0->unk8 = arg3;
    temp_4 = arg0->unkC;
    if (temp_4 != NULL) {
        temp_4->v1C(arg1, D_00465840 != 0, 0);
    }
    temp_4_2 = arg0->unk10;
    if (temp_4_2 != NULL) {
        temp_4_2->v20();
    }
    return 1;
}
}
