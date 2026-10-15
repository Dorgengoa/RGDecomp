#include "types.h"
extern "C" {

extern const u8 D_00465940[0x400];
extern void *D_00483894;

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
    virtual s32 f(s64 x0);
};
typedef struct {
    u8 pad0[0x8];
    s16 unk8;
    u8 padA[0x12];
    s32 unk1C;
    u8 pad20[0xf8];
    s64 unk118;
    s32 unk120;
    s32 unk124;
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    u32 unk138;
    s16 unk13C;
    u8 pad13E[0x2];
    s32 unk140;
    u8 pad144[0xc];
    s32 unk150;
    s32 unk154;
    s32 unk158;
    s32 unk15C;
} T3ca7c0_arg0;

s32 PartySetSpotMaybe_3ca7c0(T3ca7c0_arg0 *arg0, s64 arg1)
{
    s32 temp_2;
    void *self;
    void *vtbl;

    if (D_00483894 == NULL) {
        return 0;
    }
    self = *(void **)((u8 *)D_00483894 + 0x34);
    self = *(void **)((u8 *)self + 0xC);
    vtbl = *(void **)self;
    temp_2 = ((VC_0 *)(self))->f((s64)(s16)arg1);
    if (temp_2 == 0) {
        return 0;
    }
    if (arg0->unk8 == arg1) {
        return 1;
    }
    arg0->unk8 = (s16)arg1;
    arg0->unk1C = temp_2;
    arg0->unk118 = 0;
    arg0->unk120 = 0;
    arg0->unk124 = 0;
    {
        f32 t = (*(f32 *)D_00465940);
        arg0->unk128 = t;
        arg0->unk12C = t;
        arg0->unk130 = t;
        arg0->unk134 = t;
    }
    arg0->unk138 = 0x41300000;
    arg0->unk13C = 0;
    arg0->unk140 = 0;
    arg0->unk150 = 0;
    arg0->unk154 = 0;
    arg0->unk158 = 0;
    arg0->unk15C = 0;
    return 1;
}

}
