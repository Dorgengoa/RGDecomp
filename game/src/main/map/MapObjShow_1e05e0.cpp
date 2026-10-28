/* rgp:protos */
#line 1
#include "types.h"

struct B_001e05e0 {
    u8 pad[0x1B0];
};

struct C_001e05e0 : public B_001e05e0 {
    VC_VPTR_MEMBER;
    
    
    
    void v4(f32 a0) { VCM(void, (void *, f32), 0x18, a0); }
    
    
    void v7() { VCM0(void, 0x24); }
};

struct T_001e05e0 {
    s32 f0, f4, f8;
    C_001e05e0 *fC;
    s32 f10;
};

extern "C" s32 MapObjIsLoaded_1e0a80(T_001e05e0 *);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" void DrawListAddTexLoad_1418c0(void *, s32, f32);

extern "C" void MapObjShow_1e05e0(T_001e05e0 *p)
{
    void *r;

    if (((unsigned char)MapObjIsLoaded_1e0a80(p)) == 0) return;
    r = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(r, p->f10, 1.0f);
    p->fC->v4(1.0f);
    p->fC->v7();
}
