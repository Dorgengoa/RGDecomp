#include "types.h"
#pragma opt_common_subs off
extern "C" {

extern void **PoolGetUsedElem_36acb0(s32, s32);
extern u8 D_004659C8[0x400];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0) { VCM(void, (void *, s32), 0x450, x0); }
};
s32 ObjMgrAttackChainBegin_3ba610(void *arg0, s32 arg1)
{
    s32 temp_18;
    s32 var_19;
    void **temp_2_2;
    u8 *temp_2;

    temp_2 = *(u8 **)((u8 *)arg0 + 4);
    if (temp_2 == NULL) {
        return 0;
    }
    if (!(*(u8 *)(*(u8 **)(temp_2 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x10) == 0) {
        return 0;
    }
    temp_18 = (*(s32 *)D_004659C8);
    var_19 = 0;
    while (var_19 < temp_18) {
        temp_2_2 = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x10), var_19);
        if (temp_2_2 != NULL) {
            ((VC_0 *)(temp_2_2))->f(arg1);
        }
        var_19 += 1;
    }
    return 1;
    return 0;
}

}
