#include "types.h"
#undef NULL
#define NULL 0

class Sub {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void f(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1C, a0, a1, a2); }
};

struct Ctl {
    s32 m0;
    s32 m4;
    Sub *m8;
    Sub *mC;
    Sub *m10;
    Sub *m14;
    Sub *m18;
    Sub *m1C;
};

extern "C" {
void DataTableSetOwnerHandle_4218b0(Sub *, s32);
void DataTableSetOwnerHandle_421c30(Sub *, s32);
void DataTableSetOwnerHandle_422070(Sub *, s32);
void DataTableSetOwnerHandle_4224b0(Sub *, s32);
void DataTableSetOwnerHandle_4229f0(Sub *, s32);
extern s32 D_00465658[0x400];
extern s32 D_00465660[0x400];
extern s32 D_00465668[0x400];
extern s32 D_00465670[0x400];
extern s32 D_00465678[0x400];
extern s32 D_00465680[0x400];
}

extern "C" s32 StateTablesLoad_421080(Ctl *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    if (arg1 == 0) {
        return 0;
    }
    if (arg0->m0 == 0) {
        return 0;
    }
    arg0->m4 = arg3;
    if (arg0->m8 != NULL) {
        DataTableSetOwnerHandle_4229f0(arg0->m8, arg4);
        arg0->m8->f(arg1, D_00465658[0] != 0, 0);
    }
    if (arg0->mC != NULL) {
        DataTableSetOwnerHandle_4224b0(arg0->mC, arg4);
        arg0->mC->f(arg1, D_00465660[0] != 0, 0);
    }
    if (arg0->m10 != NULL) {
        DataTableSetOwnerHandle_422070(arg0->m10, arg4);
        arg0->m10->f(arg1, D_00465668[0] != 0, 0);
    }
    if (arg0->m14 != NULL) {
        DataTableSetOwnerHandle_421c30(arg0->m14, arg4);
        arg0->m14->f(arg1, D_00465670[0] != 0, 0);
    }
    if (arg0->m18 != NULL) {
        DataTableSetOwnerHandle_4218b0(arg0->m18, arg4);
        arg0->m18->f(arg1, D_00465678[0] != 0, 0);
    }
    if (arg0->m1C != NULL && arg2 != 0) {
        arg0->m1C->f(arg1, D_00465680[0] != 0, 0);
    }
    return 1;
}
