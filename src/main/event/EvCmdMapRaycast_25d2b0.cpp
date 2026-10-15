#include "types.h"

typedef f32 VEC[4] __attribute__((aligned(16)));

class Model {
public:
    u8 pad0[0x68];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual s32 Query(u8 *buf, f32 *pos, s32 n);
};

struct World {
    u8 pad0[0x434C];
    s32 id;
};

extern "C" {
extern void VecScale_13be00(f32 *, f32 *, f32);
extern void VecAdd_13be20(f32 *, f32 *, f32 *);
extern f32 VecDistance_13d3d0(f32 *, f32 *);
extern s32 MeshRaycastWrapper_16f610(u8 *, s32, f32 *, f32 *, f32 *, s32, s32);
extern Model *ObjRecGetLiveObject_1c5250(World *, s32);
extern void ScriptSetRefFloat_26a1c0(u8 *, f32);
extern void ScriptSetRefInt_26a1e0(u8 *, s32);
extern void ScriptArgsToVec4_26a220(f32 *, u8 *);
extern void sceVu0CopyVector(f32 *, f32 *);
extern World *D_00481F78;

s32 EvCmdMapRaycast_25d2b0(s64 *obj, s32 mode)
{
    VEC a;
    VEC b;
    VEC f;
    VEC dc[2];
    u8 buf[0xC000];
    f32 r;
    f32 dist;
    s32 i;
    Model *m;
    s32 h;

    ScriptArgsToVec4_26a220(a, (u8 *)obj);
    ScriptArgsToVec4_26a220(b, (u8 *)(obj + 3));
    obj += 6;
    sceVu0CopyVector(dc[1], a);
    sceVu0CopyVector(dc[0], b);
    dist = VecDistance_13d3d0(dc[0], dc[1]);
    r = dist;
    if (dist < 60.0f) {
        r = 60.0f;
    }
    VecAdd_13be20(dc[0], dc[0], dc[1]);
    VecScale_13be00(dc[1], dc[0], 0.5f);
    VecScale_13be00(dc[0], dc[0], 0.5f);
    for (i = 0; i < 3; i++) {
        dc[0][i] += r;
        dc[1][i] -= r;
    }
    dc[0][3] = 1.0f;
    dc[1][3] = 1.0f;
    m = ObjRecGetLiveObject_1c5250(D_00481F78, D_00481F78->id);
    if (m == NULL) {
        return 0;
    }
    h = MeshRaycastWrapper_16f610(buf, m->Query(buf, dc[0], 0x200), a, b, f, 1, 1);
    switch (mode) {
    case 10:
        ScriptSetRefFloat_26a1c0((u8 *)obj++, f[0]);
        ScriptSetRefFloat_26a1c0((u8 *)obj++, f[1]);
        ScriptSetRefFloat_26a1c0((u8 *)obj++, f[2]);
    case 7:
        ScriptSetRefInt_26a1e0((u8 *)obj, h);
        break;
    default:
        return 0;
    }
    return 1;
}
}
