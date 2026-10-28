/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

struct R3b7c00 { s8 b0, b1, b2, b3; };
class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    R3b7c00 * get(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(R3b7c00 *, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};
struct I3b7c00 { u8 pad[8]; VC *obj; };
struct D3b7c00 { u8 pad[0x58]; I3b7c00 *inner; };
struct A3b7c00 { u8 pad[0x68]; s16 v[1][2]; };
extern D3b7c00 *D_0048381C;

void CharaStatusResistSet_3b7c00(A3b7c00 *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    VC *o;
    R3b7c00 *r;

    if (D_0048381C == 0 || arg3 < 0 || arg3 >= 2) {
        return;
    }
    o = D_0048381C->inner->obj;
    r = o != 0 ? o->get(arg1, (int)(long)(arg2), (int)(long)(arg3)) : 0;
    if (r != 0) {
        arg0->v[r->b3][arg3] = arg2;
    }
}

}
