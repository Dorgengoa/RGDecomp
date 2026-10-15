#include "types.h"

class VE {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void DataTableGetCount_4250f0(s32);

extern "C" void ContainerViewGetAtFwd_425150(VE *o)
{
    o->v2();
}

extern "C" void func_00425150_e1(s32 p0)
{
    DataTableGetCount_4250f0((p0 + -0x88));
}
