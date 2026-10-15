#include "types.h"

class C32E {
public:
    u8 pad000[0xB0];
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
    virtual void v22(f32);
};

extern "C" void *GetObjRefTable_313de0(void);
extern "C" void *ScriptSlotGetInt_3348b0(void *p);
extern "C" C32E *HandleRegistryLookup_314aa0(void *a, void *b);
extern "C" f32 ScriptSlotGetFloat_334890(void *p);

extern "C" s32 ScriptCmdAttackObjSetRadius_32f380(void *p, s32 mode)
{
    void *a;
    C32E *c;

    if (mode != 2) {
        return 0;
    }
    a = GetObjRefTable_313de0();
    c = HandleRegistryLookup_314aa0(a, ScriptSlotGetInt_3348b0(p));
    if (c == 0) {
        return 1;
    }
    c->v22(ScriptSlotGetFloat_334890((u8 *)p + 8));
    return 1;
}
