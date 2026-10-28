/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
extern "C" {
extern void *PoolGetUsedElem_36acb0(s32, s32);
extern s32 InvCategoryMatches_3c8720(void *, s32, s32);
extern s32 InvGetCategoryOfId_3d56f0(s16);
extern s32 D_00465B50[];
}

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v50() { return VCM0(s32, 0x50); }
};

extern "C" s32 InvCountById_3c78d0(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_18;
    s32 temp_23;
    s32 var_17;
    s32 temp_3;
    bool var_4;
    void *temp_2;

    if (arg1 < 0) {
        return 0;
    }
    if (!(*(s32 *)((u8 *)arg0 + 0x168) != 0)) {
        return 0;
    }
    var_18 = 0;
    temp_23 = D_00465B50[0];
    var_17 = 0;
    while (var_17 < temp_23) {
        temp_2 = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x168), var_17);
        if ((temp_2 != NULL) &&
            ((arg3 != 0) || (((u64)((s64)(*(u8 *)((u8 *)temp_2 + 0xA)) << 0x3E) >> 0x3F) == 0)) &&
            (((unsigned char)InvCategoryMatches_3c8720(arg0, arg2, InvGetCategoryOfId_3d56f0(*(s16 *)((u8 *)temp_2 + 0x6)))) != 0)) {
            temp_3 = **(s16 **)((u8 *)temp_2 + 0x10);
            var_4 = false;
            if (temp_3 == arg1) {
                var_4 = true;
            } else if (temp_3 == 0x3E81 && arg1 == 0x3E82) {
                var_4 = true;
            } else if (temp_3 == 0x3E82 && arg1 == 0x3E81) {
                var_4 = true;
            } else if (temp_3 == 0x3E86 && arg1 == 0x3E87) {
                var_4 = true;
            } else if (temp_3 == 0x3E87 && arg1 == 0x3E86) {
                var_4 = true;
            }
            if (var_4) {
                var_18 += ((VObj *)temp_2)->v50();
            }
        }
        var_17 += 1;
    }
    return var_18;
}
