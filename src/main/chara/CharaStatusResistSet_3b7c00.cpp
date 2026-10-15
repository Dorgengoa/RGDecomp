#include "types.h"
extern "C" {

struct R3b7c00 { s8 b0, b1, b2, b3; };
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
    virtual R3b7c00 *get(s16);
};
struct I3b7c00 { u8 pad[8]; VC *obj; };
struct D3b7c00 { u8 pad[0x58]; I3b7c00 *inner; };
struct A3b7c00 { u8 pad[0x68]; s16 v[1][2]; };
extern D3b7c00 *D_0048381C;

void CharaStatusResistSet_3b7c00(A3b7c00 *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    VC *o;
    R3b7c00 *r;

    if (D_0048381C == 0 || arg3 < 0 || arg3 >= 2) {
        return;
    }
    o = D_0048381C->inner->obj;
    r = o != 0 ? o->get(arg1) : 0;
    if (r != 0) {
        arg0->v[r->b3][arg3] = arg2;
    }
}

}
