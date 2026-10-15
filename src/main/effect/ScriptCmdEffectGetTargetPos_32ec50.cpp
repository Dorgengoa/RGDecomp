#include "types.h"

struct Vec4 { f32 x, y, z, w; } __attribute__((aligned(16)));

struct CMgr {
    u8 pad000[0x190];
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void *v3();
    virtual void *v4();
    virtual void *v5();
    virtual void *v6();
    virtual void *v7();
    virtual void *v8();
    virtual void *v9();
    virtual void *v10();
    virtual void *v11();
};

extern "C" s32 TargetRefResolve_2e5ed0(void *, s32);
extern "C" void TargetRefGetPos_2e6a60(void *, Vec4 *);
extern "C" void ScriptSlotStoreVec3_334790(s32, Vec4 *);
extern "C" void ScriptSlotStoreIntRef_3347f0(s32, s32);
extern void *D_004826E0;

extern f32 D_0047F530;
extern f32 D_0047F534;
extern f32 D_0047F538;
extern f32 D_0047F53C;

extern "C" s32 ScriptCmdEffectGetTargetPos_32ec50(s32 args, s32 argc)
{
    Vec4 v;
    s32 flag;
    void *o;

    if (argc != 4) {
        return 0;
    }
    v.x = D_0047F530;
    v.y = D_0047F534;
    v.z = D_0047F538;
    v.w = D_0047F53C;
    flag = 0;
    if (D_004826E0 != 0) {
        o = ((CMgr *)D_004826E0)->v11();
        if (o != 0) {
            if (TargetRefResolve_2e5ed0(o, 0) != 0) {
                TargetRefGetPos_2e6a60(o, &v);
                flag = 1;
            }
        }
    }
    ScriptSlotStoreVec3_334790(args, &v);
    ScriptSlotStoreIntRef_3347f0(args + 0x18, flag);
    return 1;
}
