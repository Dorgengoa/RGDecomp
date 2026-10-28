#include "types.h"

class Obj1f5060;

class Obj1f5060 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 * v26(s16 idx) { return VCM(s16 *, (void *, s16), 0x70, idx); }
};

struct Root1f5060 {
    u8 pad00[0x60];
    void *m60;
};

struct Mid1f5060 {
    u8 pad00[0xC];
    class Obj1f5060 *m0C;
};

struct Rec1f5060 {
    u8 pad00[0x8];
    s16 *m08;
};

extern "C" struct Root1f5060 *GetWorldDataMgr_1fedf0(void);

extern "C" s32 PcDefGetCharaDataId_1f5060(s32 id)
{
    struct Rec1f5060 *r;

    r = (struct Rec1f5060 *)((struct Mid1f5060 *)GetWorldDataMgr_1fedf0()->m60)->m0C->v26((s16)id);
    if (r == 0) {
        return -1;
    }
    if (r->m08 == 0) {
        return -1;
    }
    return *r->m08;
}
