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
    virtual void v39(Vec4 *out);
};

struct Scene {
    u8 pad0000[0x4344];
    s32 m4344;
};

extern "C" Scene *GetCurrentScene_1f5be0(void);
extern "C" class Cam *ObjRecGetLiveObject_1c3bc0(Scene *s, s32 id);
extern "C" void *GetMapMgr_201a90(void);
extern "C" void MapMgrAuxAreaRender_1e13a0(void *a, Vec4 *v);
extern f32 D_0047E570[4] __attribute__((section(".sdata")));

extern "C" void MapRenderAuxAreaAtCamera_200b20(void)
{
    Vec4 v;
    Scene *s;
    class Cam *c;

    v = *(Vec4 *)D_0047E570;
    s = GetCurrentScene_1f5be0();
    c = ObjRecGetLiveObject_1c3bc0(s, s->m4344);
    if (c != 0) {
        c->v39(&v);
    }
    MapMgrAuxAreaRender_1e13a0(GetMapMgr_201a90(), &v);
}
