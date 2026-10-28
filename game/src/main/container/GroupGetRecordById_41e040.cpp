/* rgp:protos */
#line 1
#include "types.h"

struct VTableObj0041e040 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 arg1) { return VCM(s32, (void *, s16), 0x70, arg1); }
};

extern "C" VTableObj0041e040 * GroupFindByKey_41e090(void *, int);

extern "C" s32 GroupGetRecordById_41e040(s32 unused0, s32 unused1, s64 arg2)
{
    VTableObj0041e040 *self;
    s16 v;

    self = GroupFindByKey_41e090((void *)unused0, (int)unused1);
    if (self != NULL) {
        v = (s16)arg2;
        return self->v26(v);
    }
    return 0;
}
