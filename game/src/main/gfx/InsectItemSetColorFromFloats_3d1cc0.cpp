/* rgp:protos */
#line 1
#include "types.h"

class VE3D1CC0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v74(s32 a) { return VCM(int, (void *, s32), 0x130, a); }
};
extern "C" int InsectItemSetColorFromFloats_3d1cc0(VE3D1CC0 *arg0, f32 *arg1) { int rgp_v0;
    s32 r = (s32)(256.0 * arg1[0]);
    s32 g = (s32)(256.0 * arg1[2]);
    s32 b = (s32)(256.0 * arg1[3]);
    rgp_v0 = arg0->v74(b | ((g << 8) | ((r << 24) | (r << 16))));
return rgp_v0; }
