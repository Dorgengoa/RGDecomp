#include "types.h"

struct B3D3680 {
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
    virtual s32 v23();
};
struct C3D3680 : B3D3680 { u8 pad004[0x12]; s8 f16; };

extern "C" void ItemWeaponSetGrowth_3d3680(struct C3D3680 *p, s8 v)
{
    s32 r;

    p->f16 = v;
    if (v < 0) {
        p->f16 = 0;
        return;
    }
    r = p->v23();
    if (r < p->f16) {
        p->f16 = r;
    }
}
