/* rgp:protos */
#line 1
#include "types.h"

class V414 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v26(s32 a0) { return VCM(void *, (void *, s32), 0x70, a0); }
};

extern "C" void * ZonePhaseMatrixLookup_414730(V414 *o, s16 a, s16 b, s16 c, s16 d, s16 e)
{
    s32 bb = b;
    if (a == 10) bb = 1000;
    return o->v26(e + (d * 100 + (bb * 100000 + c * 1000)));
}
