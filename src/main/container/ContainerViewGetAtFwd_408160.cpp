#include "types.h"

class VE {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void DataTableGetCount_408100(s32);

extern "C" void ContainerViewGetAtFwd_408160(VE *o)
{
    o->v2();
}

extern "C" void func_00408160_e1(s32 p0)
{
    DataTableGetCount_408100((p0 + -0x88));
}
