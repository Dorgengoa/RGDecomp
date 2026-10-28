/* rgp:protos */
#line 1
#include "types.h"

class C368550 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 * f40(int rgp_fwd1 = 0) { return VCM(s32 *, (void *, int), 0x40, rgp_fwd1); }
    
    
    
    
    s32 f54(s32 a0) { return VCM(s32, (void *, s32), 0x54, a0); }
};

struct Bits7A {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
};

extern "C" s32 *DataTableHashBucketFind_368550(C368550 *arg0, u16 arg1, s32 *arg2, int rgp_a3)
{
    s32 *p;
    s32 v;
    bool ok;

    if (!((Bits7A *)((u8 *)arg0 + 0x7A))->b2) {
        return 0;
    }
    *arg2 = *(u16 *)((u8 *)arg0 + 0x82) - arg1;
    p = arg0->f40((int)(long)(arg1)) + arg1;
    while ((bool)*p && *arg2 > 0) {
        v = arg0->f54(*p) & 0xFFFF;
        if (arg1 == v) {
            return p;
        }
        if (arg1 < v) {
            break;
        }
        p++;
        (*arg2)--;
    }
    return 0;
}
