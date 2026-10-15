#include "types.h"

struct B_00386f70 {
    u8 pad[0x1B0];
};

struct C_00386f70 : public B_00386f70 {
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
    virtual void v15(f32);
    u8 pad2[0x985 - 0x1B4];
    s8 f985;
    u8 f986[2];
    f32 f988;
};

extern "C" f32 D_0047DA34;
extern "C" s32 BitArrayTest_384320(void *, s32);
extern "C" f32 WrapAngle_13c050(f32);

extern "C" void MenuObjUpdate_386f70(C_00386f70 *p, f32 v)
{
    if (p->f985 == 0) return;
    if (BitArrayTest_384320(p->f986, 8) != 0) return;
    p->v15(v);
    p->f988 = WrapAngle_13c050(D_0047DA34 + p->f988);
}
