/* rgp:protos */
#line 1
#include "types.h"

class V414 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v26(s32 a0) { return VCM(int, (void *, s32), 0x70, a0); }
};

extern "C" int ZonePhaseSetLookup_414ae0(V414 *o, s16 a, s16 b, s16 c, s16 d, s16 e)
{
    return o->v26(e + (d * 100 + (b * 100000 + c * 1000)));
}
