/* rgp:protos */
#line 1
#include "types.h"

struct VtableA {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v26(s32 arg) { VCM(void, (void *, s32), 0x70, arg); }
};

struct VtableB {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v26() { VCM0(void, 0x70); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v200(s32 arg) { VCM(void, (void *, s32), 0x328, arg); }
};

extern "C" s32 UnitBaseClearDeathTime_3b1530(void *, int, int, int);

extern "C" s32 UnitOnRevive_3bcad0(void *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 i;
    VtableA *objA;
    VtableB *objB;

    if (UnitBaseClearDeathTime_3b1530((void *)arg0, (int)arg1, (int)rgp_a2, (int)rgp_a3) == 0) {
        return 0;
    }
    i = 0;
    do {
        objA = (VtableA *)((u8 *)arg0 + i * 0x24 + 0x278);
        objA->v26(arg1);
        i += 1;
    } while (i < 0xA);
    i = 0;
    while (i < *(s16 *)((u8 *)arg0 + 0x3E6)) {
        objB = *(VtableB **)((u8 *)arg0 + i * 4 + 0x3E8);
        if (objB != 0) {
            objB->v200(arg1);
        }
        i += 1;
    }
    return 1;
}
