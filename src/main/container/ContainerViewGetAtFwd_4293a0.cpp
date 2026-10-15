#include "types.h"

class VE {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void DataTableGetCount_429340(s32);

extern "C" void ContainerViewGetAtFwd_4293a0(VE *o)
{
    o->v2();
}

extern "C" void func_004293A0_e1(s32 p0)
{
    DataTableGetCount_429340((p0 + -0x88));
}
