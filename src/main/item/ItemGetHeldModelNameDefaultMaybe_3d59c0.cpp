#include "types.h"

class V3D59C0 {
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
    virtual void v14(s32 a);
};

extern "C" s32 ItemPosInvalid_3d49a0(void);

extern "C" void ItemGetHeldModelNameDefaultMaybe_3d59c0(V3D59C0 *o)
{
    o->v14(0);
}

extern "C" bool func_003D59C0_e1(void)
{
    bool r = !ItemPosInvalid_3d49a0();
    return r;
}
