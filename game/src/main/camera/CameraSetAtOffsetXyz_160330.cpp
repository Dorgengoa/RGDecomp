/* rgp:protos */
#line 1
#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct Base160330 { u8 pad000[0xC0]; };
struct C160330 : Base160330 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v30(struct Vec4 *v) { return VCM(int, (void *, struct Vec4 *), 0x80, v); }
};

extern "C" f32 D_0047DF40;
extern "C" f32 D_0047DF44;
extern "C" f32 D_0047DF48;
extern "C" f32 D_0047DF4C;

extern "C" int CameraSetAtOffsetXyz_160330(struct C160330 *p, f32 x, f32 y, f32 z)
{ int rgp_v0;
    struct Vec4 v __attribute__((aligned(16)));

    v.x = D_0047DF40;
    v.y = D_0047DF44;
    v.z = D_0047DF48;
    v.w = D_0047DF4C;
    v.x = x;
    v.y = y;
    v.z = z;
    rgp_v0 = p->v30(&v);
return rgp_v0; }
