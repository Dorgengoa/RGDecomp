#include "types.h"
extern "C" {

class VC {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void f(s32 x0);
};

typedef struct Flags { u8 b0 : 1; u8 b1 : 1; u8 rest : 6; } Flags;

extern VC *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 D_00465B50[0x10];
extern void *D_00483890;

typedef struct O { u8 pad0[0x168]; s32 unk168; } O;

s32 InvOnBattleEndAll_3c01e0(O *arg0, s32 arg1)
{
    s32 n;
    s32 i;
    VC *p;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (!(*(u8 *)((u8 *)*(void **)((u8 *)D_00483890 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (arg0->unk168 == 0) {
        return 0;
    }
    n = D_00465B50[0];
    for (i = 0; i < n; i++) {
        p = PoolGetUsedElem_36acb0(arg0->unk168, i);
        if (p != NULL && ((Flags *)((u8 *)p + 0xA))->b1 == 0) {
            p->f(arg1);
        }
    }
    return 1;
}

}
