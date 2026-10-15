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
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
    virtual s32 v22();
    virtual s32 v23();
    virtual s32 v24();
    virtual s32 v25();
    virtual s32 v26();
    virtual s32 v27();
    virtual s32 v28();
    virtual s32 v29();
    virtual s32 v30();
    virtual s32 v31();
    virtual s32 v32();
    virtual s32 v33();
    virtual s32 v34();
    virtual s32 v35();
    virtual s32 v36();
    virtual s32 v37();
    virtual s32 v38();
    virtual s32 v39();
    virtual void v40(Vec3 *out);
};

struct Scene {
    u8 pad0000[0x4348];
    s32 m4348;
};

extern Scene *D_00481F78 __attribute__((section(".sdata")));
extern "C" class Cam *ObjRecGetLiveObject_1c3bc0(Scene *s, s32 id);
struct Slot {
    s32 a;
    s32 b;
};

extern "C" void ScriptSetRefFloat_26a1c0(struct Slot *a, f32 v);

extern "C" s32 EvCmdPrevCameraGetAt_265420(void *a0)
{
    Vec3 v;
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
