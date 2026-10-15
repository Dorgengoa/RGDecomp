#include "types.h"

class VA96 {
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

    u8 pad004[0x4BC];
    u8 b0 : 1;
    u8 b1 : 7;
};

extern "C" void CharaSetAltFormFlagMaybe_3a96a0(VA96 *o, s32 b)
{
    o->b0 = b;
    o->v12();
}
