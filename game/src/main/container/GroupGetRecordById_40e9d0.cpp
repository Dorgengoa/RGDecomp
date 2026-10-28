/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern void ** GroupFindByKey_40eaf0(void *, short);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s64 x0) { return VCM(s32, (void *, s64), 0x70, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s64 x0) { return VCM(s32, (void *, s64), 0x70, x0); }
};
s32 GroupGetRecordById_40e9d0(void *arg0, s64 arg1, s16 arg2)
{
    void **temp_2;
    void **temp_3;

    temp_3 = *(void ***)((u8 *)arg0 + 0x10);
    if (temp_3 == NULL) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x14) == 0) {
        return 0;
    }
    if (((s64)(arg1 << 0x30) >> 0x30) < 0) {
        return ((VC_0 *)(temp_3))->f(arg2);
    } else {
        temp_2 = GroupFindByKey_40eaf0(arg0, (short)(arg1));
        if (temp_2 != NULL) {
            return ((VC_1 *)(temp_2))->f(arg2);
        }
    }
    return 0;
}

}
