#include "types.h"

class VC {
public:
    u8 pad[0x1B0];
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
};

struct Big {
    u8 pad0[0x1B0];
    void *vp;
    u8 pad1B4[0x4DC - 0x1B4];
    s32 f4DC;
    u8 pad4E0[0x538 - 0x4E0];
    s32 f538;
    s32 f53C;
};

struct Obj {
    s16 f0;
    s16 f2;
    s32 f4;
    s32 f8;
    Big *c;
    s32 f10;
    s16 f14;
    s16 state;
};

struct Init {
    s32 a;
    void *b;
    s32 h0;
    s32 h1;
    s32 h2;
    s32 f14;
    s32 f18;
    u8 pad1C[0x2C - 0x1C];
    void *p2C;
    s32 n30;
    s32 pad34;
    void *p38;
    s32 n3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
};

extern "C" {
extern Big *MemStackNew_14e230(s32, s32);
extern void ModelObjPlayMotionByName_1867a0(Big *, void *, s32);
extern void InfoCfgParseAll_1afd00(Big *, Init *);
extern void ModelObjExCtor_1c4920(Big *);
extern void LoadHandlePoll_1ccb00(Obj *);
extern void LoaderReleaseHandle_1ccb70(Obj *);
extern void MapObjRelease_1e0a90(Obj *);
extern s32 GetEffectMgr_2d9040(void);
extern void *memset(void *, s32, u32);
extern u8 D_0045B428[];
extern u8 D_0045B438[];
extern u8 D_0045B440[];
extern u8 D_00470F50[];
extern s32 D_0047E180;
}

extern "C" void MapObjLoadStep_1e0850(Obj *obj, s32 heap)
{
    Big *b;
    Init in;
    s32 v;
    Big *c;
    s32 t;

    if (obj->state != 1) {
        return;
    }
    LoadHandlePoll_1ccb00(obj);
    if (heap == 0) {
        goto fail;
    }
    if (obj->f2 == -1) {
        goto fail;
    }
    if (obj->f2 == 0) {
        return;
    }
    b = MemStackNew_14e230(0x790, heap);
    if (b != 0) {
        ModelObjExCtor_1c4920(b);
        b->vp = D_00470F50;
    }
    obj->c = b;
    if (b == 0) {
        goto fail;
    }
    memset(&in, 0, sizeof(in));
    in.p2C = in.buf40;
    in.n30 = 8;
    in.p38 = in.buf60;
    in.n3C = 8;
    in.a = obj->f4;
    in.b = D_0045B428;
    in.h0 = heap;
    in.h1 = heap;
    in.h2 = heap;
    in.f14 = obj->f10;
    in.f18 = 0;
    ((VC *)obj->c)->v50();
    v = GetEffectMgr_2d9040() + 0x58;
    c = obj->c;
    c->f53C = v;
    if (v != 0) {
        t = D_0047E180;
        D_0047E180 = t + 1;
        c->f538 = t;
    }
    InfoCfgParseAll_1afd00(obj->c, &in);
    obj->c->f4DC = in.f14;
    obj->state = 2;
    switch (obj->f14) {
    case 0:
        ModelObjPlayMotionByName_1867a0(obj->c, D_0045B438, 4);
        break;
    case 1:
        ModelObjPlayMotionByName_1867a0(obj->c, D_0045B440, 4);
        break;
    }
    LoaderReleaseHandle_1ccb70(obj);
    return;
fail:
    obj->state = -1;
    MapObjRelease_1e0a90(obj);
}
