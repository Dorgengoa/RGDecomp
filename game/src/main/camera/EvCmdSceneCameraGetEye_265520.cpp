#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

struct Base39 {
    u8 pad000[0xC0];
};

class Cam : public Base39 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v39(Vec3 *out) { VCM(void, (void *, Vec3 *), 0xA4, out); }
};

struct Scene {
    s32 dummy;
};

extern "C" Scene *GetCurrentScene_1f5be0(void);
extern "C" class Cam *ObjRecGetLiveObject_1c3bc0(Scene *s, s32 id);
struct Slot {
    s32 a;
    s32 b;
};

extern "C" void ScriptSetRefFloat_26a1c0(struct Slot *a, f32 v);

extern "C" s32 EvCmdSceneCameraGetEye_265520(void *a0, s32 mode)
{
    Vec3 v __attribute__((aligned(16)));
    class Cam *c;
    struct Slot *p;

    p = (struct Slot *)a0;
    if (mode < 3) {
        return 0;
    }
    c = ObjRecGetLiveObject_1c3bc0(GetCurrentScene_1f5be0(), 1);
    if (c == 0) {
        return 0;
    }
    c->v39(&v);
    ScriptSetRefFloat_26a1c0(p++, v.x);
    ScriptSetRefFloat_26a1c0(p++, v.y);
    ScriptSetRefFloat_26a1c0(p, v.z);
    return 1;
}
