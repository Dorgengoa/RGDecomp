#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

struct Base40 {
    u8 pad000[0xC0];
};

class Cam : public Base40 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v40(Vec3 *out) { VCM(void, (void *, Vec3 *), 0xA8, out); }
};

struct Scene {
    u8 pad0000[0x4348];
    s32 m4348;
};

extern "C" Scene *D_00481F78 __attribute__((section(".sdata")));
extern "C" class Cam *ObjRecGetLiveObject_1c3bc0(Scene *s, s32 id);
struct Slot {
    s32 a;
    s32 b;
};

extern "C" void ScriptSetRefFloat_26a1c0(struct Slot *a, f32 v);

extern "C" s32 EvCmdPrevCameraGetAt_265420(void *a0)
{
    Vec3 v __attribute__((aligned(16)));
    class Cam *c;
    struct Slot *p;

    p = (struct Slot *)a0;
    c = ObjRecGetLiveObject_1c3bc0(D_00481F78, D_00481F78->m4348);
    if (c == 0) {
        return 0;
    }
    c->v40(&v);
    ScriptSetRefFloat_26a1c0(p++, v.x);
    ScriptSetRefFloat_26a1c0(p++, v.y);
    ScriptSetRefFloat_26a1c0(p, v.z);
    return 1;
}
