/* rgp:protos */
#line 1
#include "types.h"

class V414 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v26(s32 a0) { return VCM(void *, (void *, s32), 0x70, a0); }
};

extern "C" void * PlanetAreaMatrixLookup_415100(V414 *o, s16 a, s16 b, s16 c, s16 d)
{
    return o->v26(d + (c * 100 + (a * 10000000 + b * 1000)));
}
