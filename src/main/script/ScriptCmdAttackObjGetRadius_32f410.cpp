#include "types.h"

struct B_0032f410 { u8 pad[0xB0]; };
struct C_0032f410 : public B_0032f410 {
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
    virtual f32 v16();
};

struct T_0032f410 { s32 a, b; };

extern "C" void *GetObjRefTable_313de0(void);
extern "C" s32 ScriptSlotGetInt_3348b0(T_0032f410 *);
extern "C" C_0032f410 *HandleRegistryLookup_314aa0(void *, s32);
extern "C" void ScriptSlotStoreFloatRef_3347d0(void *, f32);

extern "C" s32 ScriptCmdAttackObjGetRadius_32f410(T_0032f410 *q, s32 mode)
{
    void *g;
    s32 n;
    C_0032f410 *r;

    if (mode != 2) return 0;
    g = GetObjRefTable_313de0();
    n = ScriptSlotGetInt_3348b0(q);
    r = HandleRegistryLookup_314aa0(g, n);
    if (r == 0) return 1;
    ScriptSlotStoreFloatRef_3347d0((void *)((s32)q + 8), r->v16());
    return 1;
}
