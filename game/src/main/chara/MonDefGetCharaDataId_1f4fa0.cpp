#include "types.h"

class Obj1f4fa0;

class Obj1f4fa0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 * v26(s16 idx) { return VCM(s16 *, (void *, s16), 0x70, idx); }
};

struct Root1f4fa0 {
    u8 pad00[0x64];
    void *m64;
};

struct Mid1f4fa0 {
    u8 pad00[0xC];
    class Obj1f4fa0 *m0C;
};

struct Rec1f4fa0 {
    u8 pad00[0x20];
    s16 *m20;
};

extern "C" struct Root1f4fa0 *GetWorldDataMgr_1fedf0(void);

extern "C" s32 MonDefGetCharaDataId_1f4fa0(s32 id)
{
    struct Rec1f4fa0 *r;

    r = (struct Rec1f4fa0 *)((struct Mid1f4fa0 *)GetWorldDataMgr_1fedf0()->m64)->m0C->v26((s16)id);
    if (r == 0) {
        return -1;
    }
    if (r->m20 == 0) {
        return -1;
    }
    return *r->m20;
}
