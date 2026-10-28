/* rgp:protos */
#line 1
#include "types.h"

struct B1C47E0 { u8 pad[0x1B0]; };

struct Rec1C47E0 : public B1C47E0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    void v11(f32 a, void *b) { VCM(void, (void *, void *, f32), 0x34, b, a); }
};

struct P1C47E0 {
    u8 pad[0x4360];
    f32 f4360;
    u8 pad2[0xC];
    s32 f4370;
};

extern "C" Rec1C47E0 * ObjRecGetLiveObject_1c4a90(P1C47E0 *, int);

extern "C" void SceneObjApplyWind_1c47e0(P1C47E0 *p, int rgp_a1)
{
    Rec1C47E0 *r;

    r = ObjRecGetLiveObject_1c4a90(p, (int)rgp_a1);
    if (r != 0) {
        r->v11(p->f4360, &p->f4370);
    }
}
