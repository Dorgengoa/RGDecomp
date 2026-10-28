/* rgp:protos */
#line 1
#include "types.h"

struct T_00390e60 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v68(s32 a0) { return VCM(s32, (void *, s32), 0x118, a0); }
};

extern "C" void * InsectCageMenuGetCurCageItem_391030(void);
extern "C" T_00390e60 *InsectRecSlotFindItemById_3cfad0(void *, void *);

extern "C" s32 InsectCageMenuGetInsectName_390e60(void *a)
{
    void *r;
    T_00390e60 *q;
    r = InsectCageMenuGetCurCageItem_391030();
    if (r != 0) goto ok;
    return 0;
ok:
    q = InsectRecSlotFindItemById_3cfad0(r, a);
    if (q != 0) {
        return q->v68(0);
    }
    return 0;
}
