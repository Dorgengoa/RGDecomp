#include "types.h"

struct Base332680 { u8 pad000[0x190]; };
struct C332680 : Base332680 {
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
    virtual void v13(s16 k);
};

extern "C" struct C332680 *D_004826E0;

extern "C" s32 ScriptCmdEffectSetNextEntryId_332680(void *a, s32 k)
{
    if (k == 1) goto run;
    return 0;
run:
    D_004826E0->v13((s16)k);
    return 1;
}
