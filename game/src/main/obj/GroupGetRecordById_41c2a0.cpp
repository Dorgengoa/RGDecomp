/* rgp:protos */
#line 1
#include "types.h"

extern "C" {

extern s32 GroupEntryMatchesKey_3f40e0(s32, int);
extern s32 D_004644A8[0x100];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f(s64 x0) { return VCM(void *, (void *, s64), 0x70, x0); }
};

void *GroupGetRecordById_41c2a0(void *arg0, s64 arg1, s64 arg2, s32 arg3)
{
    void *var_20;
    s32 temp_16;
    s32 var_19;
    s32 temp_4;
    void *var_2;

    var_20 = *(void **)((u8 *)arg0 + 0xC);
    if (var_20 == NULL) {
        return NULL;
    }
    temp_16 = D_004644A8[0];
    var_19 = 0;
    while (var_19 < temp_16) {
        temp_4 = *(s32 *)((u8 *)var_20 + 0x94);
        if ((temp_4 != 0) && (GroupEntryMatchesKey_3f40e0(temp_4, (int)((s64)(s16)arg2)) != 0)) {
            var_2 = ((VC_0 *)(var_20))->f((s64)(s16)arg1);
            if ((var_2 != NULL) && (arg3 != 0) && !(*(s32 *)((u8 *)var_2 + 0x48) & 1)) {
                var_2 = NULL;
            }
            if (var_2 != NULL) {
                return var_2;
            }
        }
        var_19 += 1;
        var_20 = (u8 *)var_20 + 0x98;
    }
    return NULL;
}

}
