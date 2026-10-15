#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0
extern "C" {

typedef struct Obj0Arg0 Obj0Arg0;
typedef struct {
    u8 pad0[0x34];
    void (*unk34)(Obj0Arg0 *);
} VTab0;
struct Obj0Arg0 {
    VTab0 *unk0;
    s16 unk4;
    s16 unk6;
    u8 pad8[0xA - 0x8];
    u8 bA0 : 1;
    u8 bA1 : 1;
    u8 bArest : 6;
    u8 padB[0xC - 0xB];
    s16 unkC;
    s32 unk10;
};

extern void *D_004838EC;

class VC_0 {
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
    virtual void f();
};
class VC_1 {
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
    virtual void * f(s16 x0);
};
s32 ItemSetup_3d4ff0(Obj0Arg0 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_2;
    void **temp_4;

    ((VC_0 *)(arg0))->f();
    if (arg3 < 0) {
        return 0;
    }
    if (D_004838EC == NULL) {
        return 0;
    }
    arg0->unkC = arg3;
    temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)D_004838EC + 0x40)) + 8);
    temp_2 = (s32)((VC_1 *)(temp_4))->f((s16)arg3);
    arg0->unk10 = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    arg0->unk4 = arg1;
    arg0->unk6 = arg2;
    arg0->bA0 = 0;
    arg0->bA1 = 0;
    return 1;
}

}
