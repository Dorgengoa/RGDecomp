/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK: length 0x12C vs retail 0x11C (0x10 over) after 1 round. Not re-tried. */
#include "types.h"
#pragma opt_common_subs off
extern "C" {

extern void *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 InvCategoryMatches_3c8720(void *arg0, s32 arg1, s32 arg2);
extern s32 InvIdGetMajorIndex_3d55f0(s16 arg0);
extern s32 InvGetCategoryOfId_3d56f0(s16 arg0);
extern s32 D_00465B50[4];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};
s32 InvCountInCategory_3c7ba0(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_22;
    s32 var_21;
    s32 temp_19;
    void *temp_2;
    s32 t;

    if (*(s32 *)((u8 *)arg0 + 0x168) == 0) {
        return 0;
    }
    var_22 = 0;
    var_21 = 0;
    temp_19 = D_00465B50[0];
    while (var_21 < temp_19) {
        temp_2 = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x168), var_21);
        if ((temp_2 != NULL) &&
            ((arg3 != 0) || (((u64) ((s64) *(u8 *)((u8 *)temp_2 + 0xA) << 0x3E) >> 0x3F) == 0)) &&
            (t = InvGetCategoryOfId_3d56f0(*(s16 *)((u8 *)temp_2 + 0x6)), ((unsigned char)InvCategoryMatches_3c8720(arg0, arg1, t)) != 0) &&
            ((arg2 < 0) || (arg2 == InvIdGetMajorIndex_3d55f0(*(s16 *)((u8 *)temp_2 + 0x6))))) {
            var_22 += 1;
        }
        var_21 += 1;
    }
    return var_22;
}

}
