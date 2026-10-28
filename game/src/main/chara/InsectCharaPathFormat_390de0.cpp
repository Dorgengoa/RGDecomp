/* rgp:protos */
#line 1
#include "types.h"

extern "C" void Sprintf_1343b8(s8 *, const void *, s32);
extern "C" u8 D_004640E0[];

class Obj390DE0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * slot124(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, int, int, int), 0x124, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 InsectCharaPathFormat_390de0(s8 *buf, Obj390DE0 *obj, int rgp_a2, int rgp_a3)
{
    void *r;
    void *p;

    if (buf == NULL) {
        return 0;
    }
    *buf = 0;
    if (obj == NULL) {
        return 0;
    }
    r = obj->slot124((int)(long)(obj), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r == NULL) {
        return 0;
    }
    p = *(void **)((u8 *)r + 4);
    if (p == NULL) {
        return 0;
    }
    Sprintf_1343b8(buf, D_004640E0, *(s32 *)((u8 *)p + 8));
    return 1;
}
