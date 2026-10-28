#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

struct Base39 {
    u8 pad000[0xC0];
};

class Cam : public Base39 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v39(Vec4 *out) { VCM(void, (void *, Vec4 *), 0xA4, out); }
};

struct Scene {
    u8 pad0000[0x4344];
    s32 m4344;
};

extern "C" Scene *GetCurrentScene_1f5be0(void);
extern "C" class Cam *ObjRecGetLiveObject_1c3bc0(Scene *s, s32 id);
extern "C" void *GetMapMgr_201a90(void);
extern "C" void MapDrawActiveAreas_1e17e0(void *a, Vec4 *v);
extern "C" f32 D_0047E560[4] __attribute__((section(".sdata")));

extern "C" void MapDrawPre_200c90(void)
{
    Vec4 v __attribute__((aligned(16)));
    Scene *s;
    class Cam *c;

    v = *(Vec4 *)D_0047E560;
    s = GetCurrentScene_1f5be0();
    c = ObjRecGetLiveObject_1c3bc0(s, s->m4344);
    if (c != 0) {
        c->v39(&v);
    }
    MapDrawActiveAreas_1e17e0(GetMapMgr_201a90(), &v);
}
