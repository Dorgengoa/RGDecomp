#include "types.h"

typedef struct Obj0af0 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 pad004[0xC - 0x4];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Obj0af0;

typedef struct Ret0af0 {
    s16 unk0;
    u8 pad002[0xC - 0x2];
    s32 unkC;
} Ret0af0;

class Vt0af0 {
public:
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
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual Ret0af0 *v26(s64 a);
};

extern void *D_00483994;
extern "C" void ActionPacketClear_3e3e90(Obj0af0 *self);

extern "C" Obj0af0 *ActionPacketInitFieldBeginMaybe_3e3af0(Obj0af0 *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    Vt0af0 *temp_4;
    Ret0af0 *temp_2;

    if (D_00483994 == NULL) {
        return 0;
    }
    temp_4 = *(Vt0af0 **)((u8 *)(*(void **)((u8 *)D_00483994 + 0x38)) + 8);
    temp_2 = temp_4->v26((s64)arg2);
    if (temp_2 == NULL) {
        return 0;
    }
    ActionPacketClear_3e3e90(arg0);
    arg0->unk2 = 2;
    arg0->unk3 = 0x16;
    arg0->unk0 = 2;
    arg0->unkC = arg1;
    arg0->unk10 = temp_2->unkC;
    arg0->unk14 = temp_2->unk0;
    arg0->unk18 = arg3;
    return arg0;
}
