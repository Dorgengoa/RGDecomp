#include "types.h"

struct B3B8A60 {
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
};

struct C3B8A60 : B3B8A60 {
    s16 f04;
    u8 pad006[6];
    s32 f0C;
};

extern "C" void UnitBaseResetIdsAndClear_3b8a60(struct C3B8A60 *p)
{
    p->f04 = -1;
    p->f0C = -1;
    p->v9();
}
