#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

class Base {
public:
    u8 pad000[0xC0];
};

class C : public Base {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v40(f32 *out) { VCM(void, (void *, f32 *), 0xA8, out); }
};

extern "C" C *EventSceneGetCamera_265980(void);
extern "C" void ScriptSetRefFloat_26a1c0(E8 *q, f32 v);

extern "C" s32 EvCmdCameraGetAt_265660(E8 *q, s32 n)
{
    f32 v[4] __attribute__((aligned(16)));
    C  *o;

    if (n < 3) {
        return 0;
    }
    o = EventSceneGetCamera_265980();
    if (o == 0) {
        return 0;
    }
    o->v40(v);
    ScriptSetRefFloat_26a1c0(q++, v[0]);
    ScriptSetRefFloat_26a1c0(q++, v[1]);
    ScriptSetRefFloat_26a1c0(q, v[2]);
    return 1;
}
