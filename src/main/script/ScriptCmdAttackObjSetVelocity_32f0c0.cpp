#include "types.h"

struct Base21 {
    u8 pad000[0xB0];
};

class C0 : public Base21 {
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
    virtual void v21(f32 a, f32 b, f32 c);
};

extern "C" void *GetObjRefTable_313de0(void);
extern "C" void *ScriptSlotGetInt_3348b0(void *a);
extern "C" class C0 *HandleRegistryLookup_314aa0(void *a, void *b);
extern "C" f32 ScriptSlotGetFloat_334890(void *a);

extern "C" s32 ScriptCmdAttackObjSetVelocity_32f0c0(void *a, s32 mode)
{
    void *x;
    class C0 *o;
    f32 p;
    f32 q;
    f32 r;

    if (mode != 4) {
        return 0;
    }
    x = GetObjRefTable_313de0();
    o = HandleRegistryLookup_314aa0(x, ScriptSlotGetInt_3348b0(a));
    if (o == 0) {
        return 1;
    }
    p = ScriptSlotGetFloat_334890((u8 *)a + 8);
    q = ScriptSlotGetFloat_334890((u8 *)a + 0x10);
    r = ScriptSlotGetFloat_334890((u8 *)a + 0x18);
    o->v21(p, q, r);
    return 1;
}
