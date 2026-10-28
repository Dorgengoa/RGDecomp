/* rgp:protos */
#line 1
#include "types.h"

struct B_002f8ea0 {
    u8 pad[0xDC];
};

struct C_002f8ea0 : public B_002f8ea0 {
    VC_VPTR_MEMBER;
    
    
    
    void v4() { VCM0(void, 0x18); }
};

extern "C" s32 EvObjGetAreaId_2f8f30(C_002f8ea0 *);

extern "C" void EvObjAreaFadeOnAreaUnload_2f8ea0(C_002f8ea0 *p, s32 b)
{
    if (((short)EvObjGetAreaId_2f8f30(p)) != b) return;
    if (*(f32 *)((s32)p + 0xE4) >= 1.0f) return;
    p->v4();
}
