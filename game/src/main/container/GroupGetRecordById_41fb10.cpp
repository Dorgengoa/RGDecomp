#include "types.h"

class C0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 x) { return VCM(s32, (void *, s16), 0x70, x); }
};

extern "C" class C0 *GroupFindByKey_41fb60(void *a, s16 b);

extern "C" s32 GroupGetRecordById_41fb10(void *a, s32 b, s32 c)
{
    class C0 *o;

    o = GroupFindByKey_41fb60(a, (s16)b);
    if (o != 0) {
        return o->v26((s16)c);
    }
    return 0;
}
