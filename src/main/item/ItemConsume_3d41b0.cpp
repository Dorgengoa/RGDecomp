#include "types.h"

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
    virtual s32 cnt();
    virtual void d19();
    virtual void d20();
    virtual void f(s32 x0);
};

extern "C" {
extern void ItemMarkRemoved_3d4130(VC_1 *arg0, s32 arg1);
extern s32 ItemHasCountFlag_3d44e0(VC_1 *arg0);
}

extern "C" s32 ItemConsume_3d41b0(VC_1 *arg0, s32 arg1)
{
    if (arg1 <= 0) {
        return 0;
    }
    if (arg0->cnt() < arg1) {
        return 0;
    }
    if (ItemHasCountFlag_3d44e0(arg0) == 0) {
        ItemMarkRemoved_3d4130(arg0, 1);
    } else {
        arg0->f(-arg1);
        if (arg0->cnt() == 0) {
            ItemMarkRemoved_3d4130(arg0, 1);
        }
    }
    return 1;
}
