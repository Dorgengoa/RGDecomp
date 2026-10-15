#include "types.h"
extern "C" {

extern void ScriptSlotStoreFloatRef_3347d0(s32 arg0, f32 arg1);
extern s32 ScriptSlotGetInt_3348b0(s32);

class C_4826E0 {
public:
    u8 pad[0x190];
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
    virtual void *get();
};
extern C_4826E0 *D_004826E0;

s32 ScriptCmdEffectElemGetAlpha_3303f0(s64 * arg0, s32 arg1)
{
    s32 temp_16;
    void *temp_2;

    if (arg1 != 2) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_3348b0((s32)arg0++);
    temp_2 = D_004826E0->get();
    if (temp_2 != NULL) {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, ((f32 *)((u8 *)temp_2 + 0xBC))[temp_16 * 0x30]);
    } else {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, 1.0f);
    }
    return 1;
}

}
