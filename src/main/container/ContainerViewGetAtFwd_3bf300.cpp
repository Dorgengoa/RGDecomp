#include "types.h"

class VE {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void UnitChildViewCount_3bf1d0(s32);

extern "C" void ContainerViewGetAtFwd_3bf300(VE *o)
{
    o->v2();
}

extern "C" void func_003BF300_e1(s32 p0)
{
    UnitChildViewCount_3bf1d0((p0 + -0x230));
}
